//
// Created by Ariel Saldana on 10/26/23.
//

#include "protocol/events/hello_event.h"

void hello_event::deserialize(const rapidjson::Value &value) {
    if (value.HasMember("heartbeat_interval") && value["heartbeat_interval"].IsInt()) {
        heartbeat_interval_ = value["heartbeat_interval"].GetInt();
    } else {
        std::cerr << "Error: missing or invalid 'heartbeat_interval' field." << std::endl;
    }
}

int hello_event::get_heartbeat_interval() const {
    return heartbeat_interval_;
}
