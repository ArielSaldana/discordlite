//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_WEBSOCKET_H
#define DISCORDLITE_WEBSOCKET_H

#define ASIO_STANDALONE // Use standalone ASIO

#include <iostream>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>


class WebsocketClient {
private:
    //typedef websocketpp::client<websocketpp::config::asio_client> client;
    typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
    typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
    typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;

    std::chrono::high_resolution_clock::time_point m_tls_init;
    client ws_client;

    std::string ws_uri;
    std::string ws_tls_hostname;

    void on_ws_message(client *ws_client, websocketpp::connection_hdl hdl, const message_ptr &msg);
    void on_ws_open(client *ws_client, websocketpp::connection_hdl hdl);
    void on_ws_close(client *ws_client, websocketpp::connection_hdl hdl);
    void on_ws_fail(client *ws_client, websocketpp::connection_hdl hdl);
    static void send_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg);
    context_ptr on_tls_init(const char *hostname, const websocketpp::connection_hdl&);


public:
    void connect();
    explicit WebsocketClient(const std::string &ws_uri, const std::string &ws_hostname);
};


#endif//DISCORDLITE_WEBSOCKET_H
