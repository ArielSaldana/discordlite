//
// Created by Ariel Saldana on 10/26/23.
//

#include "message_create_handler.h"
#include "http-client/send_message.h"
#include "protocol/events/dispatch_event.h"

void message_create_handler::process(const discord_client_state &client_state, const dispatch_event &event) const {
    if (event.getAuthor()->getId() != "1156420471013777580" && event.getContent().value().contains("manboober")) {
        send_message(event.getChannelId().value(), "Look at you. Sailing through the air majestically. Like an eagle. Piloting a blimp.", client_state.get_bot_token());
    }
}
