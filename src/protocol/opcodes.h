//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_OP_CODES_H
#define DISCORDLITE_OP_CODES_H

enum opcodes {
    DISPATCH = 0,
    HEARTBEAT = 1,
    IDENTIFY = 2,
    PRESENCE_UPDATE = 3,
    VOICE_STATE_UPDATE = 4,
    RESUME = 6,
    RECONNECT = 7,
    REQUEST_GUILD_MEMBER = 8,
    INVALID_SESSION = 9,
    HELLO = 10,
    HEARTBEAT_ACK = 11
};

#endif//DISCORDLITE_OP_CODES_H
