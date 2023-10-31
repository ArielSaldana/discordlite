//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_DESERIALIZABLE_H
#define DISCORDLITE_DESERIALIZABLE_H

#include "rapidjson/document.h"
#include <iostream>
#include <string>

struct deserializable {
    virtual void deserialize(const rapidjson::Value &param) = 0;

    void deserialize_string(const std::string &json) {
        rapidjson::Document d;
        d.Parse(json.c_str());
        return deserialize(d);
    };
};

#endif//DISCORDLITE_DESERIALIZABLE_H
