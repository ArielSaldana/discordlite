//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HELLO_HANDLER_H
#define DISCORDLITE_HELLO_HANDLER_H

#include "client/discord_client_state.h"
#include "handler.h"
#include "models/gateway_event_payload.h"
#include "models/hello_event.h"
#include "protocol/ping.h"

class hello_handler: public handler {
    std::unique_ptr<ping> pinger;
public:
    bool is_running = false;
    explicit hello_handler() = default;
    ~hello_handler() override = default;

//    void process(const WebsocketClient &ws_client, const hello_event &hello_event);
    void process(const discord_client_state &client_state, const gateway_event_payload &event) override;
    void send_ready_event(const discord_client_state &client_state);
    void start_heartbeat(const discord_client_state &client_state, int interval);
};


#endif//DISCORDLITE_HELLO_HANDLER_H
