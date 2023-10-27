#include "opcodes.h"

int op_codes::get_code() const {
    return code;
}

op_codes op_codes::from_int(int value) {
    switch (value) {
        case 0:
            return op_codes::DISPATCH;
        case 1:
            return op_codes::HEARTBEAT;
        case 2:
            return op_codes::IDENTIFY;
        case 3:
            return op_codes::PRESENCE_UPDATE;
        case 4:
            return op_codes::VOICE_STATE_UPDATE;
        case 6:
            return op_codes::RESUME;
        case 7:
            return op_codes::RECONNECT;
        case 8:
            return op_codes::REQUEST_GUILD_MEMBER;
        case 9:
            return op_codes::INVALID_SESSION;
        case 10:
            return op_codes::HELLO;
        case 11:
            return op_codes::HEARTBEAT_ACK;
        default:
            throw std::invalid_argument("Invalid opcode value");
    }
}

const op_codes op_codes::DISPATCH(0);
const op_codes op_codes::HEARTBEAT(1);
const op_codes op_codes::IDENTIFY(2);
const op_codes op_codes::PRESENCE_UPDATE(3);
const op_codes op_codes::VOICE_STATE_UPDATE(4);
const op_codes op_codes::RESUME(6);
const op_codes op_codes::RECONNECT(7);
const op_codes op_codes::REQUEST_GUILD_MEMBER(8);
const op_codes op_codes::INVALID_SESSION(9);
const op_codes op_codes::HELLO(10);
const op_codes op_codes::HEARTBEAT_ACK(11);
