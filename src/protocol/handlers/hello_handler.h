//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HELLO_HANDLER_H
#define DISCORDLITE_HELLO_HANDLER_H

#include "client/websocket_client.h"
#include "client/websocket_message.h"
#include "models/gateway-event-payload.h"
#include "models/hello-event.h"
#include "protocol/ping.h"


class hello_handler {
    std::unique_ptr<ping> pinger;
public:
    void process(const WebsocketClient &ws_client, const HelloEvent &hello_event);
};


#endif//DISCORDLITE_HELLO_HANDLER_H
