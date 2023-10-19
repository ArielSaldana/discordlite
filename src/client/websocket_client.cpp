//
// Created by Ariel Saldana on 9/27/23.
//

#include "websocket_client.h"
#include "message.h"

#include <utility>

void WebsocketClient::on_ws_message(client *client, websocketpp::connection_hdl hdl, const message_ptr &msg) {
    client->get_alog().write(websocketpp::log::alevel::app, "on_ws_message handler: " + msg->get_payload());
    message received_message(client, hdl, msg);
    if (on_message_cb_trigger) {
        on_message_cb_trigger(received_message);
    }
}

void WebsocketClient::on_ws_close(client *client, websocketpp::connection_hdl hdl) {
    client->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}

void WebsocketClient::on_ws_open(client *client, websocketpp::connection_hdl hdl) {
    client->get_alog().write(websocketpp::log::alevel::app, "Connection Opened");
}

void WebsocketClient::on_ws_fail(client *client, websocketpp::connection_hdl hdl) {
    client->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void WebsocketClient::send_message(WebsocketClient::client *ws_client, websocketpp::connection_hdl hdl, WebsocketClient::message_ptr msg) {
}

WebsocketClient::WebsocketClient(const std::string &ws_uri, const std::string &ws_hostname) {
    this->ws_uri = ws_uri;
    this->ws_tls_hostname = ws_hostname;

    // Setup logging levels
    ws_client.clear_access_channels(websocketpp::log::alevel::all);
    ws_client.set_access_channels(websocketpp::log::alevel::app);
    ws_client.set_access_channels(websocketpp::log::alevel::connect);
    ws_client.set_access_channels(websocketpp::log::alevel::disconnect);
    ws_client.set_access_channels(websocketpp::log::alevel::control);

    ws_client.init_asio();

    // Set handlers
    ws_client.set_close_handler([this, client = &ws_client](auto &&hdl) {
        on_ws_close(client, std::forward<decltype(hdl)>(hdl));
        if (on_connection_close_cb_trigger) {
            on_connection_close_cb_trigger();
        }
    });
    ws_client.set_fail_handler([this, client = &ws_client](auto &&hdl) {
        on_ws_fail(client, std::forward<decltype(hdl)>(hdl));
        if (on_connection_fail_cb_trigger) {
            on_connection_fail_cb_trigger();
        }
    });
    ws_client.set_open_handler([this, client = &ws_client](auto &&hdl) {
        on_ws_open(client, std::forward<decltype(hdl)>(hdl));
        if (on_connection_open_cb_trigger) {
            on_connection_open_cb_trigger();
        }
    });
    ws_client.set_message_handler([this, client = &ws_client](auto &&hdl, auto &&msg) {
        on_ws_message(client, std::forward<decltype(hdl)>(hdl), std::forward<decltype(msg)>(msg));
    });

    ws_client.set_tls_init_handler([this, client = ws_hostname.c_str()](auto &&ws_hostname) {
        return on_tls_init(client, std::forward<decltype(ws_hostname)>(ws_hostname));
    });
}

WebsocketClient::context_ptr WebsocketClient::on_tls_init(const char *hostname, const websocketpp::connection_hdl &) {
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

void WebsocketClient::connect() {
    websocketpp::lib::error_code ec;
    auto connection = ws_client.get_connection(ws_uri, ec);

    if (ec) {
        std::cout << "Connect initialization error: " << ec.message() << std::endl;
        return;
    }

    ws_client.connect(connection);
    ws_client.run();
}
