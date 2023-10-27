//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_SERIALIZABLE_H
#define DISCORDLITE_SERIALIZABLE_H

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class serializable {
    virtual rapidjson::Value to_json(rapidjson::Document::AllocatorType &allocator) = 0;
};

#endif//DISCORDLITE_SERIALIZABLE_H
