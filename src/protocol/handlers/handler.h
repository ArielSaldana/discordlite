//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HANDLER_H
#define DISCORDLITE_HANDLER_H

#include "models/gateway-event-payload.h"
#include "client/discord_client_state.h"

class handler {
public:
    virtual ~handler() = default;
    virtual void process(const discord_client_state &client_state, const GatewayEventPayload &event) = 0;

};


#endif//DISCORDLITE_HANDLER_H
