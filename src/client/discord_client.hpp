//
// Created by Ariel Saldana on 9/28/23.
//

#ifndef DISCORDLITE_DISCORD_CLIENT_HPP
#define DISCORDLITE_DISCORD_CLIENT_HPP

#include "client/discord_client_state.h"
#include "client/websocket_client.hpp"
#include "protocol/event_dispatcher.h"
#include <iostream>
#include <utility>

class discord_client {
private:
    typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
    const std::string uri = "wss://gateway.discord.gg/?v=10&encoding=json";
    const std::string hostname = "gateway.discord.gg";
    discord_client_state client_state{};
    event_dispatcher dispatcher{};

public:
    explicit discord_client(std::string bot_token, const discord_intents &intents);
    void init_handlers();
    std::string get_bot_token();
};


#endif//DISCORDLITE_DISCORD_CLIENT_HPP
