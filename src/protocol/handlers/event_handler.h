//
// Created by Ariel Saldana on 10/26/23.
//

#ifndef DISCORDLITE_EVENT_HANDLER_H
#define DISCORDLITE_EVENT_HANDLER_H

#include "protocol/events/dispatch_event.h"
#include "protocol/events/hello_event.h"
#include "protocol/handlers/dispatch_handler.h"
#include "protocol/handlers/hello_handler.h"

struct event_handler {
private:
    discord_client_state client_state;
    hello_handler hello_handle{};


public:
    explicit event_handler(discord_client_state &state);
    void operator()(const dispatch_event& event) const;
    void operator()(const hello_event& event) const;

};


#endif//DISCORDLITE_EVENT_HANDLER_H
