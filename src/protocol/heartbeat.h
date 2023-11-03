//
// Created by Ariel Saldana on 10/20/23.
//

#ifndef DISCORDLITE_HEARTBEAT_H
#define DISCORDLITE_HEARTBEAT_H

#include <asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <atomic>

class heartbeat {
private:
    asio::io_context io_context_;
    asio::steady_timer timer_;
    std::function<void()> callback_;
    std::chrono::milliseconds interval_;
    std::unique_ptr<std::thread> thread_;
    std::atomic<bool> stop_requested_;

public:
    heartbeat(std::chrono::milliseconds interval, const std::function<void()> &callback)
        : timer_(io_context_),
          callback_(callback),
          interval_(interval),
          stop_requested_(false) {
        thread_ = std::make_unique<std::thread>([this]() {
            try {
                io_context_.run();
            } catch (const std::exception& e) {
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
            thread_->join();
        }
    }

    void start_timer() {
        std::cout << "START_TIMERRRRR: " << std::to_string(interval_.count()) << std::endl;
        timer_.expires_after(interval_);
        timer_.async_wait([this](const asio::error_code &error) {
            if (error) {
                // Handle the error, e.g., log or restart the timer
                if (error == asio::error::operation_aborted) {
                    // Timer was cancelled/stopped explicitly, possibly no action needed
                } else {
                    // Log and handle other errors
                    std::cerr << "Timer error: " << error.message() << std::endl;
                }
            } else if (!stop_requested_) {
                try {
                    std::cout << "CALLLLLLLBACK" << std::endl;
                    // Execute the callback inside a try-catch to handle exceptions
                    callback_();
                } catch (const std::exception& e) {
                    // Handle exceptions from the callback
                    std::cerr << "Exception thrown from callback: " << e.what() << std::endl;
                }

                // Restart the timer
                start_timer();
            }
        });
    }

    void stop() {
        stop_requested_ = true;
        timer_.cancel(); // Cancel the timer to prevent any pending callbacks from firing
        io_context_.stop();
    }
};


#endif//DISCORDLITE_HEARTBEAT_H
