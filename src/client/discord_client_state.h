//
// Created by Ariel Saldana on 10/25/23.
//

#ifndef DISCORDLITE_DISCORD_CLIENT_STATE_H
#define DISCORDLITE_DISCORD_CLIENT_STATE_H

#include "client/websocket_client.hpp"
#include "protocol/discord_intents.h"
#include <iostream>
#include <string>

class websocket_client;

class discord_client_state {
    /*
     * The bot token
     */
    std::string bot_token_;

    /*
     * Our client shared across the code base
     */
    std::shared_ptr<websocket_client> ws_client_;

    /*
     * Our connection handle
     */
    websocketpp::connection_hdl ws_connection_hdl_;

    /*
     * is the client connected to the discord gateway
     * this should only toggle on when the ready event is received
     */
    bool is_connected_ = false;

    /*
     * Sequence number, this comes from the 's' field sent from the gateway
     * connection. otherwise send null
     */
    std::optional<int> sequence_counter_{};

    /*
     * Intents the client sends via ready event
     */
    discord_intents intents_{};


public:
    [[nodiscard]] bool is_client_connected_to_gateway() const;
    [[nodiscard]] std::string get_bot_token() const;
    [[nodiscard]] websocket_client *get_ws_client() const;
    [[nodiscard]] std::optional<int> get_sequence_counter() const;
    void set_sequence_counter(int value);
    void set_is_connected(bool connected);
    void clear_bot_token();
    void set_bot_token(std::string);
    void set_ws_client(std::shared_ptr<websocket_client> ws_client);
    void set_intents(discord_intents intents);
    discord_intents get_intents() const;
};


#endif//DISCORDLITE_DISCORD_CLIENT_STATE_H