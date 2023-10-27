//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_OP_CODES_H
#define DISCORDLITE_OP_CODES_H

#include <iostream>
#include <string>

class op_codes {
private:
    int code;

public:
    explicit op_codes(int code) : code(code) {}

    static const op_codes DISPATCH;
    static const op_codes HEARTBEAT;
    static const op_codes IDENTIFY;
    static const op_codes PRESENCE_UPDATE;
    static const op_codes VOICE_STATE_UPDATE;
    static const op_codes RESUME;
    static const op_codes RECONNECT;
    static const op_codes REQUEST_GUILD_MEMBER;
    static const op_codes INVALID_SESSION;
    static const op_codes HELLO;
    static const op_codes HEARTBEAT_ACK;

    int get_code() const;

    static op_codes from_int(int value);
};

#endif//DISCORDLITE_OP_CODES_H
