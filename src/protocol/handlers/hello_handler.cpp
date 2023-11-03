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

//void hello_handler::start_heartbeat(const discord_client_state &client_state, int interval) const {
//    heartbeat_ = std::make_unique<heartbeat>(std::chrono::milliseconds(interval), [this, &client_state]() {
//        client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::app, "Sequence from heartbeat: " + std::to_string(client_state.get_sequence_counter().value_or(0)));
//        if (client_state.is_client_connected_to_gateway()) {
//            auto s = client_state.get_sequence_counter() ? std::to_string(client_state.get_sequence_counter().value()) : "null";
//            std::stringstream ss;
//            ss << R"({"op": 1,"d": )" << s << R"(})";
//            client_state.get_ws_client()->send_message(ss.str());
//        } else {
//            client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::debug_close, "Stopping heartbeat");
//            this->heartbeat_->stop();
//        }
//    });
//    is_running = true;
//}

void hello_handler::start_heartbeat(const discord_client_state &client_state, int interval) const {
    // Safety check to prevent re-entrance
    if (is_running) {
        client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::app, "Attempted to start heartbeat while already running");
        return;
    }

    try {
        heartbeat_ = std::make_unique<heartbeat>(std::chrono::milliseconds(interval), [this, &client_state]() {
            try {
                // Your current heartbeat logic here...

                // Check if client is connected
                if (!client_state.is_client_connected_to_gateway()) {
                    throw std::runtime_error("Client disconnected from gateway");
                }
            } catch (const std::exception& e) {
                // Log the exception
                std::stringstream ss;
                ss << "Error during heartbeat: " << e.what();
                client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::app, ss.str());

                // Handle the error, for example by stopping the heartbeat
                heartbeat_->stop();
                is_running = false;

                // Possibly attempt to reconnect or restart the heartbeat...
            }
        });

        is_running = true;
    } catch (const std::exception& e) {
        // Log that we failed to start the heartbeat
        std::stringstream ss;
        ss << "Failed to start heartbeat: " << e.what();
        client_state.get_ws_client()->get_client()->get_alog().write(websocketpp::log::alevel::app, ss.str());

        // Reset the heartbeat pointer and the running flag
        heartbeat_.reset();
        is_running = false;
    }
}
