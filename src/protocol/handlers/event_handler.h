//
// Created by Ariel Saldana on 10/26/23.
//

#ifndef DISCORDLITE_EVENT_HANDLER_H
#define DISCORDLITE_EVENT_HANDLER_H

#include "protocol/events/dispatch_event.h"
#include "protocol/events/hello_event.h"
#include "protocol/events/ready_event.h"
#include "protocol/handlers/dispatch/interaction_create_handler.h"
#include "protocol/handlers/dispatch/message_create_handler.h"
#include "protocol/handlers/dispatch/ready_handler.h"
#include "protocol/handlers/dispatch_handler.h"
#include "protocol/handlers/hello_handler.h"


struct event_handler {
private:
    discord_client_state *client_state;
    hello_handler hello_handle{};
    dispatch_handler dispatch_handle{};

    /*
     * unfortunately instead of creating different opcodes for things like messages, discord uses a common opcode "0"
     * for "dispatch events" which payload can only be differentiated via the "t" field in the gateway event.
     */
    message_create_handler message_create_handle{};
    interaction_create_handler interaction_create_handle{};
    ready_handler ready_handler_{};

public:
    explicit event_handler(discord_client_state *state);
    void handle_event(const std::variant<dispatch_event, hello_event> &event_variant, const std::optional<std::string> &event_name) const;
    void operator()(const dispatch_event &event, const std::optional<std::string> &event_name) const;
    void operator()(const hello_event &event) const;
};

#endif//DISCORDLITE_EVENT_HANDLER_H
