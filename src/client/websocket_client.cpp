//
// Created by Ariel Saldana on 9/27/23.
//

#include "client/websocket_client.hpp"

void websocket_client::on_ws_close(const websocketpp::connection_hdl &) {
    ws_client->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
    scoped_lock guard(m_lock);
    is_connected_ = false;
}

void websocket_client::on_ws_fail(const websocketpp::connection_hdl &) {
    ws_client->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
    scoped_lock guard(m_lock);
    did_connection_fail_ = true;
}

void websocket_client::on_ws_open(const websocketpp::connection_hdl &hdl) {
    ws_client->get_alog().write(websocketpp::log::alevel::app, "Connection Opened");
    scoped_lock guard(m_lock);
    is_connected_ = true;
}

void websocket_client::on_ws_message(const websocketpp::connection_hdl &hdl, const message_ptr &msg) {
    ws_client->get_alog().write(websocketpp::log::alevel::app, "on_ws_message handler: " + msg->get_payload());
}

void websocket_client::send_message(const std::string &msg_str) {
    ws_client->get_alog().write(websocketpp::log::alevel::app, "sending message: " + msg_str);

    websocketpp::lib::error_code ec;
    ws_client->send(ws_connection_hdl, msg_str, websocketpp::frame::opcode::text, ec);

    if (ec) {
        std::cerr << "Send failed: " << ec.message() << std::endl;
    }
}

websocket_client::websocket_client(std::string ws_uri): ws_uri(std::move(ws_uri)) {
    // Setup logging levels
    ws_client->clear_access_channels(websocketpp::log::alevel::all);
    ws_client->set_access_channels(websocketpp::log::alevel::app);
    ws_client->set_access_channels(websocketpp::log::alevel::connect);
    ws_client->set_access_channels(websocketpp::log::alevel::disconnect);
    ws_client->set_access_channels(websocketpp::log::alevel::control);
    ws_client->set_access_channels(websocketpp::log::alevel::debug_close);
    ws_client->set_access_channels(websocketpp::log::alevel::debug_handshake);
    ws_client->set_access_channels(websocketpp::log::alevel::devel);

    ws_client->init_asio();

    // Set handlers
    ws_client->set_close_handler([this](auto &&hdl) {
        on_ws_close(std::forward<decltype(hdl)>(hdl));
        if (on_connection_close_cb_trigger) {
            on_connection_close_cb_trigger(hdl);
        }
    });
    ws_client->set_fail_handler([this](auto &&hdl) {
        on_ws_fail(std::forward<decltype(hdl)>(hdl));
        if (on_connection_fail_cb_trigger) {
            on_connection_fail_cb_trigger(hdl);
        }
    });
    ws_client->set_open_handler([this](auto &&hdl) {
        on_ws_open(std::forward<decltype(hdl)>(hdl));
        if (on_connection_open_cb_trigger) {
            on_connection_open_cb_trigger(hdl);
        }
    });

    ws_client->set_message_handler([this](auto &&hdl, auto &&msg) {
        on_ws_message(std::forward<decltype(hdl)>(hdl), std::forward<decltype(msg)>(msg));
        if (on_message_cb_trigger) {
            on_message_cb_trigger(msg->get_raw_payload());
        }
    });

    ws_client->set_tls_init_handler([this](auto &&ws_hostname) {
        return on_tls_init(std::forward<decltype(ws_hostname)>(ws_hostname));
    });
}

websocket_client::context_ptr websocket_client::on_tls_init(const websocketpp::connection_hdl &) {
    m_tls_init = std::chrono::high_resolution_clock::now();
    context_ptr ctx = websocketpp::lib::make_shared<asio::ssl::context>(asio::ssl::context::tls_client);

    try {
        ctx->set_options(asio::ssl::context::default_workarounds |
                         asio::ssl::context::no_sslv2 |
                         asio::ssl::context::no_sslv3 |
                         asio::ssl::context::single_dh_use);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return ctx;
}

void websocket_client::connect() {
    websocketpp::lib::error_code ec;
    const auto connection = ws_client->get_connection(ws_uri, ec);

    if (ec) {
        ws_client->get_alog().write(websocketpp::log::alevel::app, "Connection closed: Error getting connection from handle: " + ec.message());
        did_connection_fail_ = true;
        return;
    }

    ws_client->connect(connection);
    this->ws_connection_hdl = connection->get_handle();
    ws_client->run();
}

bool websocket_client::is_connected() {
    return (is_connected_ && !did_connection_fail_);
}
