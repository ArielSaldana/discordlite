//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_H
#define DISCORDLITE_GATEWAY_EVENT_H

#include "gateway-event-payload.h"
#include "hello-event.h"
#include <iostream>
#include <any>
#include <string>
#include <rapidjson/document.h>
#include <optional>

struct GatewayEvent {
    int op;
    std::unique_ptr<GatewayEventPayload> d;
    int s;
    std::string t;
    explicit GatewayEvent(const rapidjson::Document &doc);
};


#endif//DISCORDLITE_GATEWAY_EVENT_H
