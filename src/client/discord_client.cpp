//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.hpp"
#include "protocol/deserializer.h"
#include "protocol/handlers/dispatch_handler.h"
#include "websocket_client.hpp"
#include <memory>
#include <utility>

discord_client::discord_client(std::string bot_token, const discord_intents &intents) {
    client_state.set_bot_token(std::move(bot_token));
    client_state.set_intents(intents);
    client_state.set_ws_client(std::make_shared<websocket_client>(uri, hostname));

    event_handler_ = std::make_unique<event_handler>(this->client_state);

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
        std::visit(*handler, gateway_event.d);

    });
    client_state.get_ws_client()->connect();
}
