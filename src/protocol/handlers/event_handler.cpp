//
// Created by Ariel Saldana on 10/26/23.
//

#include "event_handler.h"


event_handler::event_handler(discord_client_state &state): client_state(state) {
}

void event_handler::operator()(const dispatch_event &event) const {
}

void event_handler::operator()(const hello_event &event) const {
    hello_handle.process(client_state, event);
}
