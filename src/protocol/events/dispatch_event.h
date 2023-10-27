//
// Created by Ariel Saldana on 10/25/23.
//

#ifndef DISCORDLITE_DISPATCH_EVENT_H
#define DISCORDLITE_DISPATCH_EVENT_H

#include "protocol/gateway_event_payload.h"
#include <iostream>

struct dispatch_event: public gateway_event_payload {
    std::string v;
};

#endif//DISCORDLITE_DISPATCH_EVENT_H
