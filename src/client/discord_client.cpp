//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.hpp"
#include "deserializer.h"
#include "protocol/handlers/dispatch_handler.h"
#include "protocol/handlers/hello_handler.h"
#include "websocket_client.hpp"
#include <memory>
#include <utility>

discord_client::discord_client(std::string bot_token, const discord_intents &intents) {
    init_handlers();

    client_state.set_bot_token(std::move(bot_token));
    client_state.set_intents(intents);
    client_state.set_ws_client(std::make_shared<websocket_client>(uri, hostname));
    client_state.get_ws_client()->on_connection_open([this](websocketpp::connection_hdl hdl) {
        client_state.set_is_connected(true);
    });
    client_state.get_ws_client()->on_connection_close([this](websocketpp::connection_hdl hdl) {
        client_state.set_is_connected(false);
    });
    client_state.get_ws_client()->on_message([this](const std::string &msg) {
        websocketpp::lib::error_code ec;
        auto gateway_event = deserializer::deserialize(msg);
        if (gateway_event.s) {
            client_state.set_sequence_counter(gateway_event.s);
        }

        dispatcher.dispatch(this->client_state, gateway_event);
    });
    client_state.get_ws_client()->connect();
}

void discord_client::discord_client::init_handlers() {
    auto hello = std::make_unique<hello_handler>();
    auto dispatch = std::make_unique<dispatch_handler>();
    dispatcher.add_handler(opcodes::DISPATCH, std::move(dispatch));
    dispatcher.add_handler(opcodes::HELLO, std::move(hello));
}
