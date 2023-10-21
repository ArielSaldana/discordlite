//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.h"
#include "client/websocket_message.h"
#include "client_state.h"
#include "deserializer.h"
#include "protocol/dispatcher.h"
#include "websocket_client.h"
#include "opcodes.h"

discord_client::discord_client(std::string uri_input, std::string hostname_input)
    : uri(std::move(uri_input)), hostname(std::move(hostname_input)) {

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

    client->on_message([&state, &client](const std::string &msg) {
        websocketpp::lib::error_code ec;
        auto gateway_event = deserializer::deserialize(msg);
//        if (gateway_event.op == opcodes::HELLO) {
//            client->send_message(R"({"op": 1,"d": 251})");
//        }
        dispatcher::dispatch(*client, gateway_event);
        state.increase_sequence_counter();
    });

    client->connect();
    std::cout << state.is_connected << std::endl;
}
