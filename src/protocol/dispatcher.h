//
// Created by Ariel Saldana on 9/29/23.
//

#ifndef DISCORDLITE_DISPATCHER_H
#define DISCORDLITE_DISPATCHER_H

#include <iostream>
#include <string>
#include "client/message.h"
#include "models/gateway_event.h"

class dispatcher {
public:
    static bool dispatch(const message &msg, const GatewayEvent &gateway_event);
};


#endif//DISCORDLITE_DISPATCHER_H
