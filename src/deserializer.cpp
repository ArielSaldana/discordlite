//
// Created by Ariel Saldana on 10/19/23.
//

#include "deserializer.h"
#include "opcodes.h"
#include "models/hello-event.h"

GatewayEvent deserializer::deserialize(const rapidjson::Document &doc) {
    GatewayEvent gwe{};

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
            if (gwe.op == opcodes::HELLO) {
                auto obj = doc["d"].GetObject();

                if (obj.HasMember("heartbeat_interval")) {
                    HelloEvent he{};
                    he.heartbeat_interval = obj["heartbeat_interval"].GetInt();
                    gwe.d = std::make_unique<HelloEvent>(he);
                }
            }
        }
    }
    return gwe;
}

GatewayEvent deserializer::deserialize(const std::string &msg) {
    rapidjson::Document d;
    d.Parse(msg.c_str());
    return deserialize(d);
}
