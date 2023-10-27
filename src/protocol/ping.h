//
// Created by Ariel Saldana on 10/20/23.
//

#ifndef DISCORDLITE_PING_H
#define DISCORDLITE_PING_H

#include <asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>

class ping {
private:
    asio::io_context io_context_;
    asio::steady_timer timer_;
    std::function<void()> callback_;
    std::chrono::milliseconds interval_;
    std::unique_ptr<std::thread> thread_;
    bool stop_requested_ = false;

public:
    ping(std::chrono::milliseconds interval, const std::function<void()> &callback)
        : timer_(io_context_),
          callback_(callback),
          interval_(interval) {
        thread_ = std::make_unique<std::thread>([this]() {
            io_context_.run();
        });

        start_timer();
    }

    ~ping() {
        stop();
        if (thread_ && thread_->joinable()) {
            thread_->join();
        }
    }

    void start_timer() {
        timer_.expires_after(interval_);
        timer_.async_wait([this](const asio::error_code &error) {
            if (!error && !stop_requested_) {
                // Execute the callback
                callback_();

                // Restart the timer
                start_timer();
            }
        });
    }

    void stop() {
        stop_requested_ = true;
        io_context_.stop();
    }
};

#endif//DISCORDLITE_PING_H
