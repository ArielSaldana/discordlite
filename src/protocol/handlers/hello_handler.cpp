//
// Created by Ariel Saldana on 10/17/23.
//

#include "hello_handler.h"
#include "iostream"
#include <asio.hpp>
#include <chrono>

void hello_handler::process(const WebsocketClient &ws_client, const HelloEvent &hello_event) {

    ping sender(std::chrono::seconds (5), [&ws_client]() {
        std::cout << "Sending heartbeat to server..." << std::endl;
        ws_client.send_message(R"({"op": 1,"d": 251})");
    });

    std::this_thread::sleep_for(std::chrono::seconds(20));
}
