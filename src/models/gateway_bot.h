//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_GATEWAY_BOT_H
#define DISCORDLITE_GATEWAY_BOT_H

#include "protocol/deserializable.h"
#include "session_start_limit.h"
#include <iostream>
#include <string>

class gateway_bot : public deserializable {
    std::string url_;
    int shards_;
    session_start_limit session_start_limit_;

public:
    void deserialize(const rapidjson::Value &param) override {
        if (param.HasMember("url") && param["url"].IsString()) {
            url_ = param["url"].GetString();
        }

        if (param.HasMember("shards") && param["shards"].IsInt()) {
            shards_ = param["shards"].GetInt();
        }

        if (param.HasMember("session_start_limit") && param["session_start_limit"].IsObject()) {
            auto session_start_limit_obj = session_start_limit{};
            session_start_limit_obj.deserialize(param["session_start_limit"].GetObject());
            session_start_limit_ = session_start_limit_obj;
        }
    }

    const std::string &getUrl() const {
        return url_;
    }
    int getShards() const {
        return shards_;
    }
    const session_start_limit &getSessionStartLimit() const {
        return session_start_limit_;
    }

    std::string get_url() {
        return url_;
    }

    int get_shards() {
        return shards_;
    }

    session_start_limit get_session_start_limit() {
        return session_start_limit_;
    }
};

#endif//DISCORDLITE_GATEWAY_BOT_H
