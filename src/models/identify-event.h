//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_IDENTIFY_EVENT_H
#define DISCORDLITE_IDENTIFY_EVENT_H

#include <iostream>
#include <string>
#include "properties.h"

struct IdentifyEvent {
    std::string token;
    int large_threshold;
    int intents;
    Properties properties;
};

#endif//DISCORDLITE_IDENTIFY_EVENT_H
