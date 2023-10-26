//
// Created by Ariel Saldana on 9/29/23.
//

#include "event_dispatcher.h"
#include "opcodes.h"
#include "opcodes_hash.h"
#include "opcodes_utilities.h"
#include "models/dispatch_event.h"

void event_dispatcher::dispatch(const discord_client_state &client_state, const gateway_event &gateway_event) {
    opcodes opcode_value = opcodes_utilities::from_int(gateway_event.op);
    auto it = handlers.find(opcode_value);
    if (it != handlers.end()) {
        if (opcode_value == opcodes::DISPATCH) {
            // If you need to handle the hello_event specifically, you can do the dynamic cast here
            auto *dispatch_gateway_event_payload = dynamic_cast<dispatch_event *>(gateway_event.d.get());
            if (dispatch_gateway_event_payload) {
                auto event_handler = dynamic_cast<dispatch_handler *>(it->second.get());
                event_handler->process(client_state, *dispatch_gateway_event_payload);
            }
        }
        if (opcode_value == opcodes::HELLO) {
            // If you need to handle the hello_event specifically, you can do the dynamic cast here
            auto *hello_gateway_event_payload = dynamic_cast<hello_event *>(gateway_event.d.get());
            if (hello_gateway_event_payload) {
                auto event_handler = dynamic_cast<hello_handler *>(it->second.get());
                event_handler->process(client_state, *hello_gateway_event_payload);
            }
        }
    }
}

void event_dispatcher::add_handler(const opcodes &opcode, std::unique_ptr<handler> handler) {
    if (!handlers.contains(opcode)) {
        handlers.emplace(opcode, std::move(handler));
    }
}
