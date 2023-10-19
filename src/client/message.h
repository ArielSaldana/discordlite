//
// Created by Ariel Saldana on 10/19/23.
//

#ifndef DISCORDLITE_MESSAGE_H
#define DISCORDLITE_MESSAGE_H

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <iostream>
#include <memory>

class message {
private:
    typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
    typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
public:
    client* websocket_client;
    websocketpp::connection_hdl hdl; // No unique_ptr needed here
    message_ptr msg;
    message(client* ws_client, const websocketpp::connection_hdl& connection_handle, const message_ptr& message)
        : websocket_client(ws_client),
          hdl(connection_handle),
          msg(message)
    {}
};


#endif//DISCORDLITE_MESSAGE_H
