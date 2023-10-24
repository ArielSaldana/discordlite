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

void hello_handler::process(const WebsocketClient &ws_client, const GatewayEventPayload &event) {
    auto token = "";

    int combinedIntents = static_cast<int>(discord_intents::GUILDS) | static_cast<int>(discord_intents::GUILD_MEMBERS) | static_cast<int>(discord_intents::AUTO_MODERATION_EXECUTION) | static_cast<int>(discord_intents::GUILD_MESSAGES) ;
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

    ws_client.send_message(msg);

    // heartbeat logic
    const auto *hello_event = dynamic_cast<const HelloEvent *>(&event);

    pinger = std::make_unique<ping>(std::chrono::milliseconds(hello_event->heartbeat_interval), [&ws_client]() {
        ws_client.send_message(R"({"op": 1,"d": 251})");
    });
    is_running = true;
}
