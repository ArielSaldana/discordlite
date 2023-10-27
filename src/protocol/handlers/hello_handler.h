//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HELLO_HANDLER_H
#define DISCORDLITE_HELLO_HANDLER_H

#include "client/discord_client_state.h"
#include "handler.h"
#include "protocol/events/hello_event.h"
#include "protocol/gateway_event_payload.h"
#include "protocol/ping.h"

class hello_handler: public handler<hello_event> {
    mutable std::unique_ptr<ping> pinger;
    mutable bool is_running = false;
public:
    explicit hello_handler() = default;
    ~hello_handler() override = default;

    void process(const discord_client_state &client_state, const hello_event &event) const override;
    void send_ready_event(const discord_client_state &client_state) const;
    void start_heartbeat(const discord_client_state &client_state, int interval) const;
};


#endif//DISCORDLITE_HELLO_HANDLER_H
