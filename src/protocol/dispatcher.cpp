//
// Created by Ariel Saldana on 9/29/23.
//

#include "dispatcher.h"
#include "opcodes.h"
#include "protocol/handlers/hello_handler.h"

bool dispatcher::dispatch(const message &message, const GatewayEvent &gateway_event) {
    if (gateway_event.op == opcodes::HELLO) {
        auto *hello_event = dynamic_cast<HelloEvent *>(gateway_event.d.get());
        std::cout << hello_event->heartbeat_interval << std::endl;
    }
    return true;
}
