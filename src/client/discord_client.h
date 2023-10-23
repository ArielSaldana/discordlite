//
// Created by Ariel Saldana on 9/28/23.
//

#ifndef DISCORDLITE_DISCORD_CLIENT_H
#define DISCORDLITE_DISCORD_CLIENT_H

#include "protocol/event_dispatcher.h"
#include <iostream>
#include <utility>

class discord_client {
private:
    bool is_ws_connection_established = false;
    bool is_connected_to_gateway = false;
    std::string uri;
    std::string hostname;
    event_dispatcher dispatcher{};

public:
    explicit discord_client(std::string uri_input, std::string hostname_input);
    void init_handlers();
};


#endif//DISCORDLITE_DISCORD_CLIENT_H
