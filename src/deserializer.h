//
// Created by Ariel Saldana on 10/19/23.
//

#ifndef DISCORDLITE_DESERIALIZER_H
#define DISCORDLITE_DESERIALIZER_H

/*
 * We have gateway events, which include gateway event payloads, or otherwise known as "d".
 * The deserializer should take in a raw string format and convert it to a gateway event object
 */

#include "models/gateway_event.h"
#include "rapidjson/document.h"

class deserializer {
public:
    static GatewayEvent deserialize(const rapidjson::Document &doc);
    static GatewayEvent deserialize(const std::string &msg);
};


#endif//DISCORDLITE_DESERIALIZER_H
