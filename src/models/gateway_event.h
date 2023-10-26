//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_H
#define DISCORDLITE_GATEWAY_EVENT_H

#include "gateway_event_payload.h"
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

struct gateway_event {
    int op;
    std::shared_ptr<gateway_event_payload> d;
    int s;
    std::string t;

    std::string to_json_string() {
        rapidjson::Document doc;
        doc.SetObject();

        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

        doc.AddMember("op", op, allocator);
//        doc.AddMember("d", d.get(), allocator);
//        propertiesObj.AddMember("os", rapidjson::Value(props.os.c_str(), allocator), allocator);
//        doc.AddMember("identify", ToJson(event, allocator), allocator);


        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        return buffer.GetString();
    }

};


#endif//DISCORDLITE_GATEWAY_EVENT_H
