//
// Created by Ariel Saldana on 9/29/23.
//

#include "dispatcher.h"
#include "client/websocket_client.h"
#include "opcodes.h"

bool dispatcher::dispatch(const WebsocketClient &ws_client, const GatewayEvent &gateway_event) {
    if (gateway_event.op == opcodes::HELLO) {
        auto *hello_event = dynamic_cast<HelloEvent *>(gateway_event.d.get());
        hello_handler h{};
        h.process(ws_client, *hello_event);
    }
    return true;
}
