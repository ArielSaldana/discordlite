//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.h"
#include "websocket_client.h"

discord_client::discord_client(std::string uri_input, std::string hostname_input)
    : uri(std::move(uri_input)), hostname(std::move(hostname_input)) {

    //    auto client = std::make_unique<WebsocketClient>("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
    WebsocketClient client("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");

    client.on_connection_open([] {
        std::cout << "CONNECTION!!" << std::endl;
    });

    client.on_message([](const std::string &raw_payload) {
        std::cout << raw_payload << std::endl;
    });

    client.connect();
}
