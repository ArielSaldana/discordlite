//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_H
#define DISCORDLITE_GATEWAY_EVENT_H

#include "dispatch_event.h"
#include "hello_event.h"
#include "protocol/gateway_event_payload.h"
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <variant>

struct gateway_event {
    int op;
    std::variant<dispatch_event, hello_event> d;
    int s;
    std::string t;
};

#endif//DISCORDLITE_GATEWAY_EVENT_H
