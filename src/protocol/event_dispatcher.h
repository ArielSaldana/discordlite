//
// Created by Ariel Saldana on 9/29/23.
//

#ifndef DISCORDLITE_EVENT_DISPATCHER_H
#define DISCORDLITE_EVENT_DISPATCHER_H

#include "client/discord_client_state.h"
#include "models/gateway_event.h"
#include "opcodes.h"
#include "protocol/handlers/handler.h"
#include "protocol/handlers/hello_handler.h"
#include <iostream>
#include <string>
#include <unordered_map>

class event_dispatcher {
    hello_handler hello{};
    std::unordered_map<opcodes, std::unique_ptr<handler>> handlers;

public:
    void dispatch(const discord_client_state &client, const GatewayEvent &gateway_event);
    void add_handler(const opcodes &, std::unique_ptr<handler>);
};


#endif//DISCORDLITE_EVENT_DISPATCHER_H
