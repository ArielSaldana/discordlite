//
// Created by Ariel Saldana on 9/29/23.
//

#include "dispatcher.h"
#include "models/gateway_event.h"
#include "rapidjson/document.h"
#include "opcodes.h"
#include "protocol/handlers/hello_handler.h"

bool dispatcher::handle_message(const std::string &msg) {
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
        auto gwe = new GatewayEvent(*doc);

        if (message->get_opcode() == opcodes::HELLO) {
            auto* hello_event = dynamic_cast<HelloEvent*>(gwe->d.get());
            hello_handler::process(*hello_event);
        }
    }

    return true;
}
