//
// Created by ariel on 9/29/2023.
//

#ifndef DISCORDLITE_CLIENT_STATE_H
#define DISCORDLITE_CLIENT_STATE_H

struct client_state {
    bool is_connected;
    int sequence_counter;

public:
    explicit client_state() = default;

    void set_is_connected(bool connected) {
        is_connected = connected;
    }

    void increase_sequence_counter() {
        sequence_counter += 1;
    }
};

#endif//DISCORDLITE_CLIENT_STATE_H
