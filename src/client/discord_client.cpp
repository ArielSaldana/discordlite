//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.hpp"
#include "http-client/get_gateway_bot_api.h"
#include "http-client/register_slash_command.h"
#include "protocol/deserializer.h"
#include "protocol/handlers/dispatch_handler.h"
#include "utilities/protocol_url_generator.h"
#include "websocket_client.hpp"
#include <memory>
#include <utility>

discord_client::discord_client(std::string bot_token, const discord_intents &intents) {
    client_state->set_bot_token(std::move(bot_token));
    client_state->set_intents(intents);
    get_gateway_connection_info();
    connect();
}

void discord_client::get_gateway_connection_info() {
    auto gateway_bot_response_str = get_gateway_bot(client_state->get_bot_token());
    gateway_connection_info.deserialize_string(gateway_bot_response_str);
}

bool discord_client::can_connect_to_gateway() {
    return gateway_connection_info.getSessionStartLimit().getRemaining() != 0;
}

void discord_client::connect() {
    if (!can_connect_to_gateway()) {
        std::cerr << "Unable to connect, no attempts remaining" << std::endl;
    }

    auto const url = protocol_url_generator::generate_url(gateway_connection_info.getUrl(), "10", "json");
    client_state->set_ws_client(std::make_shared<websocket_client>(url));

    event_handler_ = std::make_unique<event_handler>(client_state.get());

    register_slash_command(client_state->get_bot_token(), "1156420471013777580", "642866879916146699");

    client_state->get_ws_client()->on_connection_open([this](websocketpp::connection_hdl hdl) {
        client_state->set_is_connected(true);
    });

    client_state->get_ws_client()->on_connection_close([this](websocketpp::connection_hdl hdl) {
        auto con = client_state->get_ws_client()->get_client()->get_con_from_hdl(hdl);
        websocketpp::close::status::value status_code = con->get_remote_close_code();
        std::string reason = con->get_remote_close_reason();
        client_state->set_is_connected(false);

        client_state->get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::debug_close, "Connection Closed");
        client_state->get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::debug_close, "Status Code: " + std::to_string(status_code));
        client_state->get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::debug_close, "Close message:: " + reason);
    });

    client_state->get_ws_client()->on_message([this, &handler = this->event_handler_, &state = this->client_state](const std::string &msg) {
        websocketpp::lib::error_code ec;
        auto gateway_event = deserializer::deserialize(msg);
        if (gateway_event.s) {
            std::cout << "s is:" << gateway_event.s << std::endl;
            state->set_sequence_counter(gateway_event.s);
        }

        state->get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::app, "Sequence from client: " + std::to_string(state->get_sequence_counter().value_or(0)));
        handler->handle_event(gateway_event.d, gateway_event.t);
    });

    client_state->get_ws_client()->connect();
}
