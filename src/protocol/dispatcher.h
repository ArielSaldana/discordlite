//
// Created by Ariel Saldana on 9/29/23.
//

#ifndef DISCORDLITE_DISPATCHER_H
#define DISCORDLITE_DISPATCHER_H

#include <iostream>
#include <string>
#include "message.h"

class dispatcher {
public:
    static bool handle_message(const std::string &msg);
    static bool dispatch(message *msg);
};


#endif//DISCORDLITE_DISPATCHER_H
