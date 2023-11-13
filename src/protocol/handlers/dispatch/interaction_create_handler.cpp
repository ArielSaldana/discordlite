//
// Created by Ariel Saldana on 10/27/23.
//

#include "interaction_create_handler.h"
#include "http-client/ping_slash_command.h"
void interaction_create_handler::process(discord_client_state &client_state, const dispatch_event &event) const {
    ping_slash_command_response(event.getId().value(), event.getToken().value());
}
