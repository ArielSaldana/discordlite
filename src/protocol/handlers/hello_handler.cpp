//
// Created by Ariel Saldana on 10/17/23.
//

#include "hello_handler.h"
#include "handler.h"
#include "iostream"
#include <asio.hpp>
#include <chrono>

void hello_handler::process(const WebsocketClient &ws_client, const GatewayEventPayload &event) {
    //auto *hello_event = dynamic_cast<HelloEvent *>(event);
    const auto *hello_event = dynamic_cast<const HelloEvent*>(&event);

    pinger = std::make_unique<ping>(std::chrono::milliseconds (hello_event->heartbeat_interval), [&ws_client]() {
        std::cout << "Sending heartbeat to server..." << std::endl;
        ws_client.send_message(R"({"op": 1,"d": 251})");
    });

    is_running = true;
}
