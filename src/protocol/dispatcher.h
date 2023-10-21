//
// Created by Ariel Saldana on 9/29/23.
//

#ifndef DISCORDLITE_DISPATCHER_H
#define DISCORDLITE_DISPATCHER_H

#include "client/websocket_client.h"
#include "client/websocket_message.h"
#include "models/gateway_event.h"
#include <iostream>
#include <string>
#include "protocol/handlers/hello_handler.h"

class dispatcher {
    hello_handler hello{};
public:
    static bool dispatch(const WebsocketClient &ws_client, const GatewayEvent &gateway_event);
};


#endif//DISCORDLITE_DISPATCHER_H
