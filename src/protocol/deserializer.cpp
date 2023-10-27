//
// Created by Ariel Saldana on 10/19/23.
//

#include "deserializer.h"
#include "opcodes.h"
#include "protocol/events/hello_event.h"

gateway_event deserializer::deserialize(const rapidjson::Document &doc) {
    gateway_event gwe{};

    if (doc.IsObject()) {
        if (doc.HasMember("op")) {
            gwe.op = doc["op"].GetInt();
        }
        if (doc.HasMember("s") && !doc["s"].IsNull()) {
            gwe.s = doc["s"].GetInt();
        }
        if (doc.HasMember("t") && !doc["t"].IsNull()) {
            gwe.t = doc["t"].GetString();
        }
        if (doc.HasMember("d") && doc["d"].IsObject()) {
            auto &gv = doc["d"];
            auto obj = doc["d"].GetObject();

            if (gwe.op == op_codes::DISPATCH.get_code()) {
                dispatch_event event{};
                event.deserialize(gv);
                gwe.d = event;
            } else if (gwe.op == op_codes::HELLO.get_code()) {
                hello_event he{};
                he.deserialize(gv);
                gwe.d = he;
            }
        }
    }
    return gwe;
}

gateway_event deserializer::deserialize(const std::string &msg) {
    rapidjson::Document d;
    d.Parse(msg.c_str());
    return deserialize(d);
}
