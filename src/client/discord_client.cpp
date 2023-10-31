//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.hpp"
#include "http-client/register_slash_command.h"
#include "http-client/get_gateway_bot_api.h"
#include "protocol/deserializer.h"
#include "protocol/handlers/dispatch_handler.h"
#include "websocket_client.hpp"
#include <memory>
#include <utility>

discord_client::discord_client(std::string bot_token, const discord_intents &intents) {
    client_state.set_bot_token(std::move(bot_token));
    client_state.set_intents(intents);
    get_gateway_connection_info();
    connect();
}

void discord_client::get_gateway_connection_info() {
    auto gateway_bot_response_str = get_gateway_bot(client_state.get_bot_token());
    std::cout << gateway_bot_response_str << std::endl;
    gateway_connection_info.deserialize_string(gateway_bot_response_str);
}

bool discord_client::can_connect_to_gateway() {
    return gateway_connection_info.getSessionStartLimit().getRemaining() != 0;
}

void discord_client::connect() {
    if (!can_connect_to_gateway()) {
        std::cerr << "Unable to connect, no attempts remaining" << std::endl;
    }

    client_state.set_ws_client(std::make_shared<websocket_client>(gateway_connection_info.getUrl()));

    event_handler_ = std::make_unique<event_handler>(this->client_state);

    register_slash_command(client_state.get_bot_token(), "1156420471013777580", "642866879916146699");

    client_state.get_ws_client()->on_connection_open([this](websocketpp::connection_hdl hdl) {
        client_state.set_is_connected(true);
    });

    client_state.get_ws_client()->on_connection_close([this](websocketpp::connection_hdl hdl) {
        client_state.set_is_connected(false);
    });

    client_state.get_ws_client()->on_message([this, &handler = this->event_handler_](const std::string &msg) {
        websocketpp::lib::error_code ec;
        auto gateway_event = deserializer::deserialize(msg);
        if (gateway_event.s) {
            client_state.set_sequence_counter(gateway_event.s);
        }

        handler->handle_event(gateway_event.d, gateway_event.t);
    });

    client_state.get_ws_client()->connect();
}
