//
// Created by Ariel Saldana on 11/11/23.
//

#include "ready_handler.h"

void ready_handler::process(discord_client_state &client_state, const dispatch_event &event) const {
    if (event.get_resume_url().has_value()) {
        client_state.set_resume_url(*event.get_resume_url());
        std::cerr << "Resume URL is: " << client_state.get_resume_url() << std::endl;
    }
}
