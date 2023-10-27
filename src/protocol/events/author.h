//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_AUTHOR_H
#define DISCORDLITE_AUTHOR_H

#include "protocol/serializable.h"
#include <iostream>
#include <string>
#include "protocol/deserializable.h"

struct author : public deserializable {
    std::string username_;
    std::string id_;
//    author(std::string username, std::string id)
//        : username_(std::move(username)), id_(std::move(id)) {}

    void deserialize(const rapidjson::Value &value) override {
        if (value.HasMember("username") && value["username"].IsString()) {
            username_ = value["username"].GetString();
        }
        if (value.HasMember("id") && value["id"].IsString()) {
            id_ = value["id"].GetString();
        }

    }

    const std::string &getUsername() const {
        return username_;
    }
    const std::string &getId() const {
        return id_;
    }
};


#endif//DISCORDLITE_AUTHOR_H
