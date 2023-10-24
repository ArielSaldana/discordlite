//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HANDLER_H
#define DISCORDLITE_HANDLER_H

#include "client/websocket_client.hpp"
#include "models/gateway-event-payload.h"

class handler {
public:
    virtual ~handler() = default;
    virtual void process(const WebsocketClient &ws_client, const GatewayEventPayload &event) = 0;

};


#endif//DISCORDLITE_HANDLER_H
