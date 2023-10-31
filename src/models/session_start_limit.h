//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_SESSION_START_LIMIT_H
#define DISCORDLITE_SESSION_START_LIMIT_H

#include "protocol/deserializable.h"

struct session_start_limit: public deserializable {
    int max_concurrency_{};
    int remaining_{};
    int reset_after_{};
    int total_{};

    void deserialize(const rapidjson::Value &param) override {
        if ( param.HasMember("max_concurrency") && param["max_concurrency"].GetInt()) {
            max_concurrency_ = param["max_concurrency"].GetInt();
        }

        if ( param.HasMember("remaining") && param["remaining"].GetInt()) {
            remaining_ = param["remaining"].GetInt();
        }

        if ( param.HasMember("reset_after") && param["reset_after"].GetInt()) {
            reset_after_ = param["reset_after"].GetInt();
        }

        if ( param.HasMember("total") && param["total"].GetInt()) {
            total_ = param["total"].GetInt();
        }
    }

    int getMaxConcurrency() const {
        return max_concurrency_;
    }
    int getRemaining() const {
        return remaining_;
    }
    int getResetAfter() const {
        return reset_after_;
    }
    int getTotal() const {
        return total_;
    }
};

#endif//DISCORDLITE_SESSION_START_LIMIT_H
