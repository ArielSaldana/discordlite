//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.hpp"
#include "deserializer.h"
#include "opcodes.h"
#include "protocol/handlers/hello_handler.h"
#include "websocket_client.hpp"
#include <memory>

discord_client::discord_client(std::string uri_input, std::string hostname_input)
    : uri(std::move(uri_input)), hostname(std::move(hostname_input)) {
    init_handlers();

    ws_client = std::make_shared<WebsocketClient>(uri, hostname);
    ws_client->on_connection_open([this](websocketpp::connection_hdl hdl) {
        set_is_connected(true);
    });
    ws_client->on_connection_close([this] (websocketpp::connection_hdl hdl) {
        set_is_connected(false);
    });
    ws_client->on_message([this](const std::string &msg) {
        websocketpp::lib::error_code ec;
        auto gateway_event = deserializer::deserialize(msg);
        dispatcher.dispatch(*ws_client, gateway_event);
    });
    ws_client->connect();
}

void discord_client::discord_client::init_handlers() {
    auto hello = std::make_unique<hello_handler>();
    dispatcher.add_handler(opcodes::HELLO, std::move(hello));
}

bool discord_client::is_client_connected_to_gateway() const {
    return is_connected;
}

void discord_client::set_sequence_counter(int value) {
    *sequence_counter = value;
}

void discord_client::set_is_connected(bool connected) {
    is_connected = connected;
}
