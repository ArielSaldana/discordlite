//
// Created by Ariel Saldana on 10/17/23.
//

#include "hello_handler.h"
#include "handler.h"
#include "iostream"
#include "models/gateway_event.h"
#include "models/identify-event.h"
#include "protocol/discord_intents.h"
#include <chrono>

void hello_handler::process(const discord_client_state &client_state, const GatewayEventPayload &event) {
    send_ready_event(client_state);

    // heartbeat logic
    const auto *hello_event = dynamic_cast<const HelloEvent *>(&event);
    start_heartbeat(client_state, hello_event->heartbeat_interval);
}

void hello_handler::send_ready_event(const discord_client_state &client_state) {
    auto token = client_state.get_bot_token();

    int combinedIntents = static_cast<int>(discord_intents::GUILDS) | static_cast<int>(discord_intents::GUILD_MEMBERS) | static_cast<int>(discord_intents::AUTO_MODERATION_EXECUTION) | static_cast<int>(discord_intents::GUILD_MESSAGES);
    auto identify_event = std::make_shared<IdentifyEvent>(token, 0, combinedIntents, properties{"os", "browser", "device"});

    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
    doc.AddMember("op", 2, allocator);
    doc.AddMember("d", identify_event->to_json(allocator), allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    auto msg = buffer.GetString();

    client_state.get_ws_client()->send_message(msg);
}

void hello_handler::start_heartbeat(const discord_client_state &client_state, int interval) {
    pinger = std::make_unique<ping>(std::chrono::milliseconds(interval), [&client_state, ws_client = client_state.get_ws_client()]() {
        auto s = client_state.get_sequence_counter().has_value() ? std::to_string(client_state.get_sequence_counter().value()) : "null";
        std::stringstream ss;
        ss << R"({"op": 1,"d": )" << s << R"(})";
        ws_client->send_message(std::format(R"({{"op": 1,"d": {}}})", s));

        ws_client->send_message(ss.str());
    });
    is_running = true;
}
