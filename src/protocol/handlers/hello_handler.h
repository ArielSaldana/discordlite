//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HELLO_HANDLER_H
#define DISCORDLITE_HELLO_HANDLER_H

#include "models/gateway-event-payload.h"
#include "models/hello-event.h"


class hello_handler {
public:
    static void process(const HelloEvent &payload);
};


#endif//DISCORDLITE_HELLO_HANDLER_H
