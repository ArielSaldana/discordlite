//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.hpp"
#include "http-client/get_gateway_bot_api.h"
#include "http-client/register_slash_command.h"
#include "protocol/deserializer.h"
#include "utilities/protocol_url_generator.h"
#include "websocket_client.hpp"

discord_client::discord_client(std::string bot_token, const discord_intents &intents) {
    client_state->set_bot_token(std::move(bot_token));
    client_state->set_intents(intents);
    get_gateway_connection_info();
}

void discord_client::get_gateway_connection_info() {
    const auto gateway_bot_response_str = get_gateway_bot(client_state->get_bot_token());
    gateway_connection_info.deserialize_string(gateway_bot_response_str);
}

auto discord_client::can_connect_to_gateway() -> bool {
    return gateway_connection_info.getSessionStartLimit().getRemaining() != 0;
}

void discord_client::init_ws_client_events() {
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

        std::cerr << "Attempting to reconnect\n";
        connect(true);
    });

    client_state->get_ws_client()->on_message([this, &handler = this->event_handler_, &state = this->client_state](const std::string &msg) {
        auto gateway_event = deserializer::deserialize(msg);
        if (gateway_event.s != 0) {
            state->set_sequence_counter(gateway_event.s);
        }
        handler->handle_event(gateway_event.d, gateway_event.t);
    });
}
void discord_client::connect(const bool should_resume) {
    if (!can_connect_to_gateway()) {
        should_client_reconnect_ = false;
        std::cerr << "Unable to connect, no attempts remaining" << std::endl;
    }

    std::string url;

    if (should_resume) {
        url = protocol_url_generator::generate_url(client_state->get_resume_url(), "10", "json");
    } else {
        url = protocol_url_generator::generate_url(gateway_connection_info.getUrl(), "10", "json");
    }

    client_state->set_ws_client(std::make_shared<websocket_client>(url));
    event_handler_ = std::make_unique<event_handler>(client_state.get());

    register_slash_command(client_state->get_bot_token(), "1156420471013777580", "642866879916146699");

    init_ws_client_events();

    do {
        client_state->get_ws_client()->connect();
    } while (should_client_reconnect_);
}

void discord_client::set_should_client_reconnect(const bool should_reconnect) {
    should_client_reconnect_ = should_reconnect;
}

