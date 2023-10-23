//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.h"
#include "client/websocket_message.h"
#include "client_state.h"
#include "deserializer.h"
#include "websocket_client.h"
#include "opcodes.h"
#include "protocol/handlers/hello_handler.h"
#include <memory>

discord_client::discord_client(std::string uri_input, std::string hostname_input)
    : uri(std::move(uri_input)), hostname(std::move(hostname_input)) {

    init_handlers();

    //    auto client = std::make_unique<WebsocketClient>("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
//    WebsocketClient client("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
    auto client = std::make_shared<WebsocketClient>("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
    client_state state{};

    client->on_connection_open([this, &state] {
        state.set_is_connected(true);
    });

    client->on_connection_close([this, &state] {
        state.set_is_connected(false);
    });


    typedef websocketpp::client<websocketpp::config::asio_tls_client> clientt;
    client->on_message([this, &state, &client](const std::string &msg) {
        websocketpp::lib::error_code ec;
        auto gateway_event = deserializer::deserialize(msg);
        dispatcher.dispatch(*client, gateway_event);
        state.increase_sequence_counter();
    });

    client->connect();
    std::cout << state.is_connected << std::endl;
}

void discord_client::init_handlers() {
    auto hello = std::make_unique<hello_handler>();
    dispatcher.add_handler(opcodes::HELLO, std::move(hello));
}
