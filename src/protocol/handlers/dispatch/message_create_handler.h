//
// Created by Ariel Saldana on 10/26/23.
//

#ifndef DISCORDLITE_MESSAGE_CREATE_HANDLER_H
#define DISCORDLITE_MESSAGE_CREATE_HANDLER_H

#include "protocol/handlers/handler.h"
#include "protocol/events/dispatch_event.h"
#include "protocol/handlers/dispatch_handler.h"

struct message_create_handler: dispatch_handler {
    void process(const discord_client_state &client_state, const dispatch_event &event) const override;
};


#endif//DISCORDLITE_MESSAGE_CREATE_HANDLER_H
