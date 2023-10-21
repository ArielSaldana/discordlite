//
// Created by Ariel Saldana on 10/19/23.
//

#ifndef DISCORDLITE_WEBSOCKET_MESSAGE_H
#define DISCORDLITE_WEBSOCKET_MESSAGE_H

#include <iostream>
#include <memory>
#include <utility>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

class websocket_message {
private:
    typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
    typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

public:
    client *websocket_client;
    websocketpp::connection_hdl hdl;// No unique_ptr needed here
    message_ptr msg;
    websocket_message(client *ws_client, websocketpp::connection_hdl handle, const message_ptr &message)
        : websocket_client(ws_client),
          hdl(std::move(handle)),
          msg(message) {}
};


#endif//DISCORDLITE_WEBSOCKET_MESSAGE_H
