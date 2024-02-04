//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_H
#define DISCORDLITE_GATEWAY_EVENT_H

#include "dispatch_event.h"
#include "hello_event.h"
#include "ready_event.h"
#include "utilities/json_utils.h"

#include <memory>
#include <protocol/opcodes.h>
#include <variant>

struct gateway_event : private deserializable {
    int op;
    std::variant<dispatch_event, hello_event> d;
    int s;
    std::string t;

    void deserialize(const rapidjson::Value &value) override {
        if (value.HasMember("op")) {
            this->op = value["op"].GetInt();

            /* s and t are null when op is not 0 */
            if (this->op == op_codes::DISPATCH.get_code()) {
                if (value.HasMember("s") && !value["s"].IsNull()) {
                    this->s = value["s"].GetInt();
                }
                if (value.HasMember("t") && !value["t"].IsNull()) {
                    this->t = value["t"].GetString();
                }
            }
        }

        if (value.HasMember("d") && value["d"].IsObject()) {
            auto &gv = value["d"];
            auto obj = value["d"].GetObject();

            if (this->op == op_codes::DISPATCH.get_code()) {
                dispatch_event event{};
                event.deserialize(gv);
                this->d = event;
            } else if (this->op == op_codes::HELLO.get_code()) {
                hello_event he{};
                he.deserialize(gv);
                this->d = he;
            }
        }
    }

    static std::unique_ptr<gateway_event> from_string(std::string json_string) {
        std::unique_ptr<gateway_event> gateway_event_ptr(new gateway_event());
        gateway_event_ptr->deserialize(json_utils::value_from_string(json_string));
        return gateway_event_ptr;
    }
};

#endif//DISCORDLITE_GATEWAY_EVENT_H
