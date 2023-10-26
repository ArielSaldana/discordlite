//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_HELLO_H
#define DISCORDLITE_HELLO_H

#include "models/gateway_event_payload.h"
#include "deserializable.h"

struct hello_event : public gateway_event_payload, public deserializable {
    int heartbeat_interval;
    void deserialize(const rapidjson::Document& document) override {
        // Check if the "heartbeat_interval" field exists and is an integer
        if (document.HasMember("heartbeat_interval") && document["heartbeat_interval"].IsInt()) {
            heartbeat_interval = document["heartbeat_interval"].GetInt();
        } else {
            std::cerr << "Error: missing or invalid 'heartbeat_interval' field." << std::endl;
        }
    }
};

#endif//DISCORDLITE_HELLO_H
