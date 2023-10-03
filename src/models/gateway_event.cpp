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

GatewayEvent::GatewayEvent(const rapidjson::Document &doc) {
    //    GatewayEvent event;
    if (doc.IsObject()) {
        if (doc.HasMember("op")) {
            op = doc["op"].GetInt();
        }

        if (doc.HasMember("s")) {
            s = doc["s"].GetInt();
        }

        if (doc.HasMember("t")) {
            t = doc["t"].GetString();
        }

        if (doc.HasMember("d")) {
            if (op == opcodes::HELLO) {

            }
        }

    }
//    return event;
}

