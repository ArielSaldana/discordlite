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
#include <rapidjson/document.h>

struct GatewayEvent {
    typedef std::variant<GatewayEventPayload<HelloEvent>> event_data;
    int op;
    event_data d;
    int s;
    std::string t;

    GatewayEvent(const rapidjson::Document &doc);
//    GatewayEvent deserialize(const rapidjson::Document &document) const override;
};


#endif//DISCORDLITE_GATEWAY_EVENT_H
