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

using client = websocketpp::client<websocketpp::config::asio_tls_client>;
using message_ptr = websocketpp::config::asio_client::message_type::ptr;
class websocket_client {
private:
    using scoped_lock = websocketpp::lib::lock_guard<websocketpp::lib::mutex>;
    using context_ptr = websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context>;

    /*
     * Set to true if the connection has failed
     */
    bool did_connection_fail_ = false;

    /*
     * Set to true if a websocket connection has been established
     */
    bool is_connected_ = false;

    /*
     * time point for tls initialization
     */
    std::chrono::high_resolution_clock::time_point m_tls_init;

    /*
     * A shared pointer for the client
     */
    std::shared_ptr<client> ws_client = std::make_shared<client>();

    /*
     * The connection handle
     */
    websocketpp::connection_hdl ws_connection_hdl;

    /*
     * Mutex lock for operations since the connection handle is not thread safe by default
     */
    websocketpp::lib::mutex m_lock;

    /*
     * The websocket URI
     */
    std::string ws_uri;

    /*
     * The websocket hostname
     */
    std::string ws_tls_hostname;

    /*
     * Callback hooks to forward events
     */
    std::function<void(websocketpp::connection_hdl hdl)> on_connection_open_cb_trigger = nullptr;
    std::function<void(websocketpp::connection_hdl hdl)> on_connection_close_cb_trigger = nullptr;
    std::function<void(websocketpp::connection_hdl hdl)> on_connection_fail_cb_trigger = nullptr;
    std::function<void(const std::string &msg)> on_message_cb_trigger = nullptr;

    /*
     * Handlers for events
     */
    void on_ws_open(const websocketpp::connection_hdl &hdl);
    void on_ws_close(const websocketpp::connection_hdl &hdl);
    void on_ws_fail(const websocketpp::connection_hdl &hdl);
    void on_ws_message(const websocketpp::connection_hdl &hdl, const message_ptr &msg);
    auto on_tls_init(const websocketpp::connection_hdl &) -> context_ptr;

public:
    auto is_connected() -> bool;
    void send_message(const std::string &msg_str);
    void connect();
    explicit websocket_client(std::string ws_uri);

    template<typename Callable>
    void on_connection_open(Callable callback) {
        this->on_connection_open_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_connection_close(Callable callback) {
        this->on_connection_close_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_connection_fail(Callable callback) {
        this->on_connection_fail_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_message(Callable &&callback) {
        this->on_message_cb_trigger = std::forward<Callable>(callback);
    }

    auto get_client() -> client * {
        return ws_client.get();
    }
};


#endif//DISCORDLITE_WEBSOCKET_H
