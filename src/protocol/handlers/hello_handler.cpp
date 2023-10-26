//
// Created by Ariel Saldana on 10/17/23.
//

#include "hello_handler.h"
#include "handler.h"
#include "iostream"
#include "models/gateway_event.h"
#include "models/identify_event.h"
#include "protocol/discord_intents.h"
#include <chrono>

void hello_handler::process(const discord_client_state &client_state, const gateway_event_payload &event) {
    // don't call again if this is already running
    if (is_running) {
        return;
    }

    send_ready_event(client_state);

    // heartbeat logic
    const auto *hello_gateway_event_payload = dynamic_cast<const hello_event *>(&event);
    start_heartbeat(client_state, hello_gateway_event_payload->heartbeat_interval);
}

void hello_handler::send_ready_event(const discord_client_state &client_state) {
    auto token = client_state.get_bot_token();
    auto combined_intents = client_state.get_intents();
    auto identify_ev = std::make_shared<identify_event>(token, 0, combined_intents.value(), properties{"os", "browser", "device"});

    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
    doc.AddMember("op", 2, allocator);
    doc.AddMember("d", identify_ev->to_json(allocator), allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    auto msg = buffer.GetString();

    client_state.get_ws_client()->send_message(msg);
}

void hello_handler::start_heartbeat(const discord_client_state &client_state, int interval) {
    pinger = std::make_unique<ping>(std::chrono::milliseconds(interval), [&client_state]() {
        auto s = client_state.get_sequence_counter() ? std::to_string(client_state.get_sequence_counter().value()) : "null";
        std::stringstream ss;
        ss << R"({"op": 1,"d": )" << s << R"(})";
        client_state.get_ws_client()->send_message(ss.str());
    });
    is_running = true;
}
