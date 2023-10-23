//
// Created by Ariel Saldana on 10/22/23.
//

#ifndef DISCORDLITE_OPCODES_UTILITIES_H
#define DISCORDLITE_OPCODES_UTILITIES_H

#include <iostream>
#include "opcodes.h"

class opcodes_utilities {
public:
    static opcodes from_int(int value) {
        switch(value) {
            case 0: return opcodes::DISPATCH;
            case 1: return opcodes::HEARTBEAT;
            case 10: return opcodes::HELLO;
            case 11: return opcodes::HEARTBEAT_ACK;
            default: throw std::invalid_argument("Invalid opcode value");
        }
    }
};


#endif//DISCORDLITE_OPCODES_UTILITIES_H
