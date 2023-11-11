//
// Created by Ariel Saldana on 10/17/23.
//

#ifndef DISCORDLITE_HANDLER_H
#define DISCORDLITE_HANDLER_H

#include "client/discord_client_state.h"

template<typename T>
class handler {
public:
    virtual ~handler() = default;
    virtual void process(const discord_client_state &client_state, const T &event) const = 0;
};


#endif//DISCORDLITE_HANDLER_H
