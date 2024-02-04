//
// Created by Ariel Saldana on 2/3/24.
//

#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <iostream>
#include <rapidjson/document.h>
#include <string>>

class json_utils {
public:
    static rapidjson::Value value_from_string(const std::string& json_string);
};


#endif//JSON_UTILS_H
