//
// Created by Ariel Saldana on 9/28/23.
//

#ifndef DISCORDLITE_DISCORD_CLIENT_HPP
#define DISCORDLITE_DISCORD_CLIENT_HPP

#include "client/discord_client_state.h"
#include "client/websocket_client.hpp"
#include "models/gateway_bot.h"
#include "protocol/handlers/event_handler.h"
#include <iostream>
#include <utility>

class discord_client {
private:
    typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
    discord_client_state client_state{};
    std::unique_ptr<event_handler> event_handler_;
    gateway_bot gateway_connection_info{};
    void get_gateway_connection_info();
    void connect();
    bool can_connect_to_gateway();

public:
    explicit discord_client(std::string bot_token, const discord_intents &intents);
};


#endif//DISCORDLITE_DISCORD_CLIENT_HPP
