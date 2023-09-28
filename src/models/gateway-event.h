//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_H
#define DISCORDLITE_GATEWAY_EVENT_H

#include "gateway-event-payload.h"
#include "hello-event.h"
#include <iostream>
#include <any>
#include <variant>
#include <string>

struct GatewayEvent {
    int op;
    std::variant<GatewayEventPayload<HelloEvent>> d;
    int s;
    std::string t;
};

#endif//DISCORDLITE_GATEWAY_EVENT_H
