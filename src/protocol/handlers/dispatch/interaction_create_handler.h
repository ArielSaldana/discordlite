//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_INTERACTION_CREATE_HANDLER_H
#define DISCORDLITE_INTERACTION_CREATE_HANDLER_H

#include "protocol/events/dispatch_event.h"
#include "protocol/handlers/dispatch_handler.h"
#include "protocol/handlers/handler.h"

struct interaction_create_handler : dispatch_handler {
    void process(const discord_client_state &client_state, const dispatch_event &event) const override;
};


#endif//DISCORDLITE_INTERACTION_CREATE_HANDLER_H
