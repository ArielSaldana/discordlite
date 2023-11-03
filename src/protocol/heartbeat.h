//
// Created by Ariel Saldana on 10/20/23.
//

#ifndef DISCORDLITE_HEARTBEAT_H
#define DISCORDLITE_HEARTBEAT_H

#include <asio.hpp>
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

class heartbeat {
private:
    asio::io_context io_context_;
    asio::steady_timer timer_ = asio::steady_timer(io_context_, 3000);
    std::function<void()> callback_;
    std::chrono::milliseconds interval_;
    std::unique_ptr<std::thread> thread_;
    std::atomic<bool> stop_requested_;

public:
    heartbeat(std::chrono::milliseconds interval, const std::function<void()> &callback)
        : callback_(callback),
          interval_(interval),
          stop_requested_(false) {
        thread_ = std::make_unique<std::thread>([this]() {
            ///std::cout << err << std::endl;
            try {
                std::cout << "before" << std::endl;
                io_context_.run();
                std::cout << "after" << std::endl;

            } catch (const std::exception &e) {
                // Handle exceptions thrown from the io_context
                std::cerr << "Exception thrown from io_context: " << e.what() << std::endl;
            }
        });

        std::cout << "THREADDDDDEDDD" << std::endl;
        start_timer();
    }

    // Deleted the default constructor to prevent uninitialized usage
    heartbeat() = delete;

    ~heartbeat() {
        stop();
        if (thread_ && thread_->joinable()) {
            std::cout << "thread joined" << std::endl;
            thread_->join();
        }
    }

    void start_timer() {
        std::cout << "START_TIMERRRRR: " << std::to_string(interval_.count()) << std::endl;
        timer_.expires_after(interval_);
        timer_.async_wait([this](auto error) {
            std::cout << "meow" << std::endl;
            start_timer();
        });
    }

    void stop() {
        std::cout << "Stopped" << std::endl;
        stop_requested_ = true;
        timer_.cancel();// Cancel the timer to prevent any pending callbacks from firing
        io_context_.stop();
    }
};


#endif//DISCORDLITE_HEARTBEAT_H
