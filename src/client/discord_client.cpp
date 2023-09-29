//
// Created by Ariel Saldana on 9/28/23.
//

#include "discord_client.h"
#include "client_state.h"
#include "websocket_client.h"

discord_client::discord_client(std::string uri_input, std::string hostname_input)
    : uri(std::move(uri_input)), hostname(std::move(hostname_input)) {

    //    auto client = std::make_unique<WebsocketClient>("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
    WebsocketClient client("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
    client_state state{};

    client.on_connection_open([&state] {
        state.set_is_connected(true);
    });

    client.on_connection_close([&state] {
        state.set_is_connected(false);
    });

    client.on_message([&state](const std::string &raw_payload) {
        std::cout << raw_payload << std::endl;
        state.increase_sequence_counter();
    });

    client.connect();
    std::cout << state.is_connected << std::endl;

}
