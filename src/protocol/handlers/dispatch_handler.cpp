//
// Created by Ariel Saldana on 10/25/23.
//

#include "dispatch_handler.h"
#include "protocol/events/dispatch_event.h"
void dispatch_handler::process(const discord_client_state &client_state, const dispatch_event &event) const {

    const auto *dispatch_gateway_event_payload = dynamic_cast<const dispatch_event *>(&event);
    std::cout << "MOOOOOOOOOOOOO" << std::endl;
}

