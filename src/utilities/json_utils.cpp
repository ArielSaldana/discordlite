//
// Created by Ariel Saldana on 2/3/24.
//

#include "json_utils.h"

rapidjson::Value json_utils::value_from_string(const std::string& json_string) {
    rapidjson::Document d;
    d.Parse(json_string.c_str());
    rapidjson::Value value(d, d.GetAllocator());
    return value;
}

