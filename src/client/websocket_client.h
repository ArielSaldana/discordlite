//
// Created by Ariel Saldana on 9/27/23.
//

#ifndef DISCORDLITE_WEBSOCKET_H
#define DISCORDLITE_WEBSOCKET_H

#define ASIO_STANDALONE 1
#define _WEBSOCKETPP_CPP11_THREAD_ 1

#include <iostream>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <mutex>

#include "websocket_message.h"

class WebsocketClient {
private:
    typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
    typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
    typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;

    std::chrono::high_resolution_clock::time_point m_tls_init;
//    client ws_client;
    std::shared_ptr<client> ws_client = std::make_shared<client>();
    websocketpp::connection_hdl ws_connection_hdl;

    websocketpp::lib::mutex m_lock;

    std::string ws_uri;
    std::string ws_tls_hostname;

    // callback hooks to forward events to client
    std::function<void()> on_connection_open_cb_trigger = nullptr;
    std::function<void()> on_connection_close_cb_trigger = nullptr;
    std::function<void()> on_connection_fail_cb_trigger = nullptr;
//    std::function<void(const websocket_message &msg)> on_message_cb_trigger = nullptr;
//    std::function<void(client *client, const websocketpp::connection_hdl &hdl)> on_message_cb_trigger = nullptr;
    std::function<void(const std::string &msg)> on_message_cb_trigger = nullptr;
    void on_ws_message(client *ws_client, const websocketpp::connection_hdl& hdl, const message_ptr &msg);
    void on_ws_open(client *ws_client, websocketpp::connection_hdl hdl);
    void on_ws_close(client *ws_client, websocketpp::connection_hdl hdl);
    void on_ws_fail(client *ws_client, websocketpp::connection_hdl hdl);
//    static void send_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg);
    context_ptr on_tls_init(const char *hostname, const websocketpp::connection_hdl &);

public:
    void send_message(const std::string &msg_str) const;
    void connect();
    explicit WebsocketClient(const std::string &ws_uri, const std::string &ws_hostname);

    template<typename Callable>
    void on_connection_open(Callable callback)
    {
        this->on_connection_open_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_connection_close(Callable callback)
    {
        this->on_connection_close_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_connection_fail(Callable callback)
    {
        this->on_connection_fail_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_message(Callable &&callback)
    {
        this->on_message_cb_trigger = std::forward<Callable>(callback);
    }

    client * get_client() {
        return ws_client.get();
    }
};


#endif//DISCORDLITE_WEBSOCKET_H
