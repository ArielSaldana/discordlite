//
// Created by Ariel Saldana on 10/17/23.
//

#include "hello_handler.h"
#include "handler.h"
#include "iostream"
#include "protocol/discord_intents.h"
#include "protocol/events/gateway_event.h"
#include "protocol/events/identify_event.h"
#include <chrono>
#include <memory>

void hello_handler::process(const discord_client_state &client_state, const hello_event &event) const {
    // don't call again if this is already running
    if (is_running) {
        std::cerr << "Attempted to begin another heartbeat thread while a thread is already running: " << std::endl;
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
    pinger = std::make_unique<ping>(std::chrono::milliseconds(interval), [&client_state]() {
        auto s = client_state.get_sequence_counter() ? std::to_string(client_state.get_sequence_counter().value()) : "null";
        std::stringstream ss;
        ss << R"({"op": 1,"d": )" << s << R"(})";
        client_state.get_ws_client()->send_message(ss.str());
    });
    std::cout << "Started running thread" << std::endl;
    is_running = true;
}
