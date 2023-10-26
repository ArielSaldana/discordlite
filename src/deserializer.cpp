//
// Created by Ariel Saldana on 10/19/23.
//

#include "deserializer.h"
#include "models/hello_event.h"
#include "opcodes.h"

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
        if (doc.HasMember("d")) {
//            auto& gv = doc["d"];
            auto obj = doc["d"].GetObject();
            if (gwe.op == opcodes::HELLO) {
                if (obj.HasMember("heartbeat_interval")) {
                    hello_event he{};
                    he.heartbeat_interval = obj["heartbeat_interval"].GetInt();
                    gwe.d = std::make_unique<hello_event>(he);
                }
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
