//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HELLO_HANDLER_H
#define DISCORDLITE_HELLO_HANDLER_H

#include "client/discord_client_state.h"
#include "handler.h"
#include "protocol/events/hello_event.h"
#include "protocol/heartbeat.h"

class hello_handler : public handler<hello_event> {
    mutable std::unique_ptr<heartbeat> heartbeat_;
    mutable bool is_running = false;

public:
    explicit hello_handler() = default;
    ~hello_handler() override {
        std::cout << "deleting(de-referencing) hello_handler" << std::endl;
        if (heartbeat_) {
            heartbeat_->stop();
        }
    }

    void process(discord_client_state &client_state, const hello_event &event) const override;
    void send_ready_event(const discord_client_state &client_state) const;
    void start_heartbeat(const discord_client_state &client_state, int interval) const;
    void periodically_send_heartbeat(const discord_client_state &client_state, asio::steady_timer* timer, const std::error_code& /*e*/) const;
};


#endif//DISCORDLITE_HELLO_HANDLER_H
