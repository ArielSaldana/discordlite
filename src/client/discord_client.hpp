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

class discord_client {
private:
    using client = websocketpp::client<websocketpp::config::asio_tls_client>;
    std::unique_ptr<discord_client_state> client_state = std::make_unique<discord_client_state>();
    std::unique_ptr<event_handler> event_handler_;
    gateway_bot gateway_connection_info{};
    void get_gateway_connection_info();
    void init_ws_client_events();
    auto can_connect_to_gateway() -> bool;

    // add a function
    bool should_client_reconnect_ = true;

public:
    void connect(bool should_resume = false);
    void set_should_client_reconnect(bool should_reconnect);
    explicit discord_client(std::string bot_token, const discord_intents &intents);
};

#endif//DISCORDLITE_DISCORD_CLIENT_HPP
