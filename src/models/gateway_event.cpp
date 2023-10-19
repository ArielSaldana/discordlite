//
// Created by Ariel Saldana on 10/2/23.
//

#include "gateway_event.h"
#include "opcodes.h"
//
//GatewayEvent GatewayEvent::deserialize(const rapidjson::Document &document) override
//{
//    // Implementation here...
//}

//GatewayEvent::GatewayEvent(const rapidjson::Document &doc) {
//    //    GatewayEvent event;
//    if (doc.IsObject()) {
//        if (doc.HasMember("op")) {
//            op = doc["op"].GetInt();
//        }
//        if (doc.HasMember("s") && !doc["s"].IsNull()) {
//            s = doc["s"].GetInt();
//        }
//        if (doc.HasMember("t") && !doc["t"].IsNull()) {
//            t = doc["t"].GetString();
//        }
//        if (doc.HasMember("d")) {
//            if (op == opcodes::HELLO) {
//                auto obj = doc["d"].GetObject();
//
//                if (obj.HasMember("heartbeat_interval")) {
//                    HelloEvent he{};
//                    he.heartbeat_interval = obj["heartbeat_interval"].GetInt();
//                    d = std::make_unique<HelloEvent>(he);
//                }
//            }
//        }
//    }
//    //    return event;
//}
