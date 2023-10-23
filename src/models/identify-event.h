//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_IDENTIFY_EVENT_H
#define DISCORDLITE_IDENTIFY_EVENT_H

#include <iostream>
#include <string>
#include "properties.h"
#include "serializable.h"

struct IdentifyEvent: public serializable, GatewayEventPayload {
    std::string token;
    int large_threshold;
    int intents;
    properties properties_;

    IdentifyEvent(std::string token, int large_threshold, int intents, properties props)
        : token(std::move(token)), large_threshold(large_threshold), intents(intents), properties_(std::move(props)) {}

    rapidjson::Value to_json(rapidjson::Document::AllocatorType& allocator) override {
        rapidjson::Value identifyObj(rapidjson::kObjectType);
        identifyObj.AddMember("token", rapidjson::Value(token.c_str(), allocator), allocator);
//        identifyObj.AddMember("large_threshold", large_threshold, allocator);
        identifyObj.AddMember("intents", intents, allocator);
        identifyObj.AddMember("properties", properties_.to_json(allocator), allocator);
        return identifyObj;
    };
};

#endif//DISCORDLITE_IDENTIFY_EVENT_H
