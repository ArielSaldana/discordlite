//
// Created by Ariel Saldana on 9/29/23.
//

#include "dispatcher.h"
#include "rapidjson/document.h"

bool dispatcher::handle_message(const std::string &msg) {
    std::cout << msg << std::endl;

    rapidjson::Document d;
    d.Parse(msg.c_str());

    if (d.HasParseError()) {
        std::cerr << "Error parsing JSON" << std::endl;
        return false;
    }

    if (d.IsObject()) {
        auto opcode = d["op"].GetInt();
        auto *event_message = new message(opcode, std::move(d));
        dispatch(event_message);
    }

    return true;
}

bool dispatcher::dispatch(message *message) {
    auto doc = message->get_json_document();
    if (doc->IsObject()) {
        std::cout << message->get_opcode() << std::endl;
    }
}
