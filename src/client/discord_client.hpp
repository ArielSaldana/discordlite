//
// Created by Ariel Saldana on 9/28/23.
//

#ifndef DISCORDLITE_DISCORD_CLIENT_HPP
#define DISCORDLITE_DISCORD_CLIENT_HPP

#include "protocol/event_dispatcher.h"
#include <iostream>
#include <utility>

class discord_client {
private:
    typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
    std::string uri;
    std::string hostname;
    event_dispatcher dispatcher{};

    /*
     * Our client shared across the code base
     */
    std::shared_ptr<WebsocketClient> ws_client;

    /*
     * Our connection handle
     */
    websocketpp::connection_hdl ws_connection_hdl;

    /*
     * is the client connected to the discord gateway
     * this should only toggle on when the ready event is received
     */
    bool is_connected = false;

    /*
     * Sequence number, this comes from the 's' field sent from the gateway
     * connection. otherwise send null
     */
    std::optional<int> sequence_counter{};

    [[nodiscard]] bool is_client_connected_to_gateway() const;
    void set_sequence_counter(int value);
    void set_is_connected(bool connected);

public:
    explicit discord_client(std::string uri_input, std::string hostname_input);
    void init_handlers();
};


#endif//DISCORDLITE_DISCORD_CLIENT_HPP
