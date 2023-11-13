//
// Created by Ariel Saldana on 11/11/23.
//

#ifndef READY_HANDLER_H
#define READY_HANDLER_H

#include "protocol/events/dispatch_event.h"
#include "protocol/handlers/dispatch_handler.h"
#include "protocol/handlers/handler.h"

struct ready_handler final : dispatch_handler {
    void process(discord_client_state &client_state, const dispatch_event &event) const override;
};



#endif //READY_HANDLER_H
