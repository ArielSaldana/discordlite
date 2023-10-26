//
// Created by Ariel Saldana on 9/29/23.
//

#include "event_dispatcher.h"
#include "opcodes.h"
#include "opcodes_hash.h"
#include "opcodes_utilities.h"

void event_dispatcher::dispatch(const discord_client_state &client_state, const GatewayEvent &gateway_event) {
    opcodes opcode_value = opcodes_utilities::from_int(gateway_event.op);
    auto it = handlers.find(opcode_value);
    if (it != handlers.end()) {
        if (opcode_value == opcodes::HELLO) {
            // If you need to handle the HelloEvent specifically, you can do the dynamic cast here
            auto *hello_event = dynamic_cast<HelloEvent *>(gateway_event.d.get());
            if (hello_event) {
                auto event_handler = dynamic_cast<hello_handler *>(it->second.get());
                event_handler->process(client_state, *hello_event);
            }
        }
    }
}

void event_dispatcher::add_handler(const opcodes &opcode, std::unique_ptr<handler> handler) {
    if (!handlers.contains(opcode)) {
        handlers.emplace(opcode, std::move(handler));
    }
}
