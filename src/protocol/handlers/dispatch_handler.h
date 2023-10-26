//
// Created by Ariel Saldana on 10/25/23.
//

#ifndef DISCORDLITE_DISPATCH_HANDLER_H
#define DISCORDLITE_DISPATCH_HANDLER_H

#include "protocol/handlers/handler.h"

class dispatch_handler: public handler {
public:
    void process(const discord_client_state &client_state, const gateway_event_payload &event) override;
};


#endif//DISCORDLITE_DISPATCH_HANDLER_H
