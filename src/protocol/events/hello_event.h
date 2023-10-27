//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_HELLO_H
#define DISCORDLITE_HELLO_H

#include "protocol/deserializable.h"
#include "protocol/gateway_event_payload.h"
#include <iostream>

struct hello_event : public gateway_event_payload, public deserializable {
    void deserialize(const rapidjson::Value &value) override;
    [[nodiscard]] int get_heartbeat_interval() const;
private:
    int heartbeat_interval_;
};

#endif//DISCORDLITE_HELLO_H
