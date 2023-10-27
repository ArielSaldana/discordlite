//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_DESERIALIZABLE_H
#define DISCORDLITE_DESERIALIZABLE_H

#include "rapidjson/document.h"
struct deserializable {
    virtual void deserialize(const rapidjson::Value &param) = 0;
};

#endif//DISCORDLITE_DESERIALIZABLE_H
