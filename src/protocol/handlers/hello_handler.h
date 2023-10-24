//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HELLO_HANDLER_H
#define DISCORDLITE_HELLO_HANDLER_H

#include "client/websocket_client.hpp"
#include "handler.h"
#include "models/gateway-event-payload.h"
#include "models/hello-event.h"
#include "protocol/ping.h"

class hello_handler: public handler {
    std::unique_ptr<ping> pinger;
public:
    bool is_running;
    explicit hello_handler() = default;
    ~hello_handler() override = default;

//    void process(const WebsocketClient &ws_client, const HelloEvent &hello_event);
    void process(const WebsocketClient &ws_client, const GatewayEventPayload &event) override;
};


#endif//DISCORDLITE_HELLO_HANDLER_H
