//
// Created by Ariel Saldana on 11/11/23.
//

#ifndef READY_EVENT_H
#define READY_EVENT_H

#include "protocol/deserializable.h"
#include "protocol/gateway_event_payload.h"
#include <iostream>
#include <string>

class ready_event final : public gateway_event_payload, public deserializable {
    std::string session_id;
    std::string session_type;
    std::string resume_gateway_url;

public:

    void deserialize(const rapidjson::Value &value) override {
        if (value.HasMember("session_id") && value["session_id"].IsString()) {
            session_id = value["session_id"].GetString();
        }

        if (value.HasMember("session_type") && value["session_type"].IsString()) {
            session_id = value["session_type"].GetString();
        }

        if (value.HasMember("resume_gateway_url") && value["resume_gateway_url"].IsString()) {
            session_id = value["resume_gateway_url"].GetString();
        }
    };

    [[nodiscard]] auto get_resume_url() const -> std::string {
        return resume_gateway_url;
    }
};

#endif //READY_EVENT_H
