//
// Created by Ariel Saldana on 10/25/23.
//

#ifndef DISCORDLITE_DISPATCH_HANDLER_H
#define DISCORDLITE_DISPATCH_HANDLER_H

#include "protocol/events/dispatch_event.h"
#include "protocol/handlers/handler.h"

class dispatch_handler: public handler<dispatch_event> {
public:
    void process(const discord_client_state &client_state, const dispatch_event &event) const override;
};


#endif//DISCORDLITE_DISPATCH_HANDLER_H
