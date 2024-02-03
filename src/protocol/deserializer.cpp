//
// Created by Ariel Saldana on 10/19/23.
//

#include "deserializer.h"
#include "opcodes.h"
#include "protocol/events/hello_event.h"

auto deserializer::deserialize(const rapidjson::Document &doc) -> gateway_event {
    gateway_event gateway_ev{};

    if (doc.IsObject()) {
        if (doc.HasMember("op")) {
            gateway_ev.op = doc["op"].GetInt();

            /* s and t are null when op is not 0 */
            if (gateway_ev.op == op_codes::DISPATCH.get_code()) {
                if (doc.HasMember("s") && !doc["s"].IsNull()) {
                    gateway_ev.s = doc["s"].GetInt();
                }
                if (doc.HasMember("t") && !doc["t"].IsNull()) {
                    gateway_ev.t = doc["t"].GetString();
                }
            }
        }

        if (doc.HasMember("d") && doc["d"].IsObject()) {
            auto &gv = doc["d"];
            auto obj = doc["d"].GetObject();

            if (gateway_ev.op == op_codes::DISPATCH.get_code()) {
                dispatch_event event{};
                event.deserialize(gv);
                gateway_ev.d = event;
            } else if (gateway_ev.op == op_codes::HELLO.get_code()) {
                hello_event he{};
                he.deserialize(gv);
                gateway_ev.d = he;
            }
        }
    }
    return gateway_ev;
}

auto deserializer::deserialize(const std::string &msg) -> gateway_event {
    rapidjson::Document d;
    d.Parse(msg.c_str());
    return deserialize(d);
}
