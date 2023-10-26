//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_H
#define DISCORDLITE_GATEWAY_EVENT_H

#include "gateway_event_payload.h"
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

struct gateway_event {
    int op;
    std::shared_ptr<gateway_event_payload> d;
    int s;
    std::string t;
};


#endif//DISCORDLITE_GATEWAY_EVENT_H
