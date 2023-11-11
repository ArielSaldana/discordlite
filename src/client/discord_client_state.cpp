//
// Created by Ariel Saldana on 10/25/23.
//

#include "discord_client_state.h"

auto discord_client_state::get_sequence_counter() const -> std::optional<int> {
    return sequence_counter_;
}

auto discord_client_state::is_client_connected_to_gateway() const -> bool {
    return is_connected_;
}

void discord_client_state::set_sequence_counter(int value) {
    sequence_counter_ = value;
}

void discord_client_state::set_is_connected(bool connected) {
    is_connected_ = connected;
}

auto discord_client_state::get_bot_token() const -> std::string {
    return bot_token_;
}

void discord_client_state::clear_bot_token() {
    bot_token_ = "";
}

void discord_client_state::set_bot_token(std::string bot_token) {
    bot_token_ = std::move(bot_token);
}

auto discord_client_state::get_ws_client() const -> websocket_client * {
    return ws_client_.get();
}

void discord_client_state::set_ws_client(std::shared_ptr<websocket_client> ws_client) {
    ws_client_ = std::move(ws_client);
}

void discord_client_state::set_intents(discord_intents intents) {
    this->intents_ = intents;
}

auto discord_client_state::get_intents() const -> discord_intents {
    return intents_;
}

void discord_client_state::set_should_reconnect(bool value) {
    should_reconnect_ = value;
}

auto discord_client_state::get_should_reconnect() const -> bool {
    return should_reconnect_;
}
