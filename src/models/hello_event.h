//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_HELLO_H
#define DISCORDLITE_HELLO_H

struct hello_event : gateway_event_payload {
    int heartbeat_interval;
};

#endif//DISCORDLITE_HELLO_H
