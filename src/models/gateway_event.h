//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_H
#define DISCORDLITE_GATEWAY_EVENT_H

#include "gateway-event-payload.h"
#include <iostream>

struct GatewayEvent {
    int op;
    std::shared_ptr<GatewayEventPayload> d;
    int s;
    std::string t;

};


#endif//DISCORDLITE_GATEWAY_EVENT_H
