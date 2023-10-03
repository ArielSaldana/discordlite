//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_DESERIALIZABLE_H
#define DISCORDLITE_DESERIALIZABLE_H

#include "rapidjson/document.h"
template <typename T>
struct deserializable {
    deserializable();
    virtual deserializable deserialize(const rapidjson::Document &document) = 0;
};

#endif//DISCORDLITE_DESERIALIZABLE_H
