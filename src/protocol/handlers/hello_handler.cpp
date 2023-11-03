//
// Created by Ariel Saldana on 10/17/23.
//

#include "hello_handler.h"
#include "client/discord_client_state.h"
#include "handler.h"
#include "iostream"
#include "protocol/discord_intents.h"
#include "protocol/events/gateway_event.h"
#include "protocol/events/identify_event.h"
#include <chrono>
#include <memory>

#include <asio.hpp>
#include <functional>
#include <iostream>
#include <thread>

void hello_handler::process(const discord_client_state &client_state, const hello_event &event) const {
    // don't call again if this is already running
    if (is_running) {
        client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::app, "Heartbeat is already running");
        return;
    }

    start_heartbeat(client_state, event.get_heartbeat_interval());
    send_ready_event(client_state);
}

void hello_handler::send_ready_event(const discord_client_state &client_state) const {
    auto token = client_state.get_bot_token();
    auto combined_intents = client_state.get_intents();
    auto identify_ev = identify_event(token, 0, combined_intents.value(), properties{"os", "browser", "device"});

    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
    doc.AddMember("op", 2, allocator);
    doc.AddMember("d", identify_ev.to_json(allocator), allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    auto msg = buffer.GetString();

    client_state.get_ws_client()->send_message(msg);
}

void hello_handler::start_heartbeat(const discord_client_state &client_state, int interval) const {

    // Any program that uses ASIO need to have at least one io_context object
    asio::io_context io;

    // Create a steady_timer instance, setting its expiry time 3 seconds from now
    asio::steady_timer timer(io, asio::chrono::seconds(3));

    // Set the timer to execute the periodic_task function
    timer.async_wait([this, capture0 = &timer, &client_state](auto &&PH1) { return periodically_send_heartbeat(client_state, capture0, std::forward<decltype(PH1)>(PH1)); });

    // Run the io_context in a separate thread
    std::thread t([&io]() { io.run(); });

    // Do other things in the main thread if needed...

    // Wait for the thread to finish

    t.detach();
    //t.join();
}
void hello_handler::periodically_send_heartbeat(const discord_client_state &client_state, asio::steady_timer *timer, const std::error_code & /*e*/) const {
    std::cout << "Task executed every 3 seconds." << std::endl;

    client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::app, "Sequence from heartbeat: " + std::to_string(client_state.get_sequence_counter().value_or(0)));
    if (client_state.is_client_connected_to_gateway()) {
        auto s = client_state.get_sequence_counter() ? std::to_string(client_state.get_sequence_counter().value()) : "null";
        std::stringstream ss;
        ss << R"({"op": 1,"d": )" << s << R"(})";
        client_state.get_ws_client()->send_message(ss.str());
    } else {
        client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::debug_close, "Stopping heartbeat");
        this->heartbeat_->stop();
    }
    is_running = true;

    // Reschedule the timer for another 3 seconds in the future
    timer->expires_at(timer->expiry() + asio::chrono::seconds(3));

    // Posts the timer event again
    timer->async_wait([this, timer, &client_state](auto &&PH1) { return periodically_send_heartbeat(client_state, timer, std::forward<decltype(PH1)>(PH1)); });
}
