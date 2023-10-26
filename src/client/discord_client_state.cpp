//
// Created by Ariel Saldana on 10/25/23.
//

#include "discord_client_state.h"
#include <utility>

std::optional<int> discord_client_state::get_sequence_counter() const {
    return sequence_counter_;
}

bool discord_client_state::is_client_connected_to_gateway() const {
    return is_connected_;
}

void discord_client_state::set_sequence_counter(int value) {
    *sequence_counter_ = value;
}

void discord_client_state::set_is_connected(bool connected) {
    is_connected_ = connected;
}

std::string discord_client_state::get_bot_token() const {
    return bot_token_;
}

void discord_client_state::clear_bot_token() {
    bot_token_ = "";
}

void discord_client_state::set_bot_token(std::string bot_token) {
    bot_token_ = std::move(bot_token);
}

websocket_client *discord_client_state::get_ws_client() const {
    return ws_client_.get();
}

void discord_client_state::set_ws_client(std::shared_ptr<websocket_client> ws_client) {
    ws_client_ = std::move(ws_client);
}

void discord_client_state::set_intents(discord_intents intents) {
    this->intents_ = intents;
}

discord_intents discord_client_state::get_intents() const {
    return intents_;
}
