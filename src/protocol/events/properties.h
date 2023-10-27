//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_PROPERTIES_H
#define DISCORDLITE_PROPERTIES_H

#include "protocol/serializable.h"
#include <iostream>
#include <string>

struct properties : public serializable {
    std::string os;
    std::string browser;
    std::string device;

    properties(std::string os, std::string browser, std::string device)
        : os(std::move(os)), browser(std::move(browser)), device(std::move(device)) {}

    rapidjson::Value to_json(rapidjson::Document::AllocatorType &allocator) override {
        rapidjson::Value propertiesObj(rapidjson::kObjectType);
        propertiesObj.AddMember("os", rapidjson::Value(os.c_str(), allocator), allocator);
        propertiesObj.AddMember("browser", rapidjson::Value(browser.c_str(), allocator), allocator);
        propertiesObj.AddMember("device", rapidjson::Value(device.c_str(), allocator), allocator);
        return propertiesObj;
    }
};

#endif//DISCORDLITE_PROPERTIES_H
