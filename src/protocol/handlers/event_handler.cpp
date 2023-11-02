//
// Created by Ariel Saldana on 10/26/23.
//

#include "event_handler.h"

event_handler::event_handler(discord_client_state *state) : client_state(state) {
}

void event_handler::operator()(const dispatch_event &event, const std::optional<std::string> &event_name) const {
    if (event_name) {
        const std::string &name = *event_name;
        if (name == "MESSAGE_CREATE") {
            message_create_handle.process(*client_state, event);
        } else if (name == "INTERACTION_CREATE") {
            interaction_create_handle.process(*client_state, event);
        } else {
            client_state->get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::devel, "Unknown event name:" + name);
            dispatch_handle.process(*client_state, event);
        }
    } else {
        std::cout << "Event name is not provided" << std::endl;
    }
}

void event_handler::operator()(const hello_event &event) const {
    hello_handle.process(*client_state, event);
}

void event_handler::handle_event(const std::variant<dispatch_event, hello_event> &event_variant, const std::optional<std::string> &event_name) const {
    std::visit([this, &event_name](auto &&event) {
        using EventType = std::decay_t<decltype(event)>;
        if constexpr (std::is_same_v<EventType, dispatch_event>) {
            this->operator()(event, event_name);
        } else {
            this->operator()(event);
        }
    },
               event_variant);
}
