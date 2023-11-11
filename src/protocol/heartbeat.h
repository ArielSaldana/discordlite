#ifndef DISCORDLITE_HEARTBEAT_H
#define DISCORDLITE_HEARTBEAT_H

#include <asio.hpp>
#include <atomic>
#include <functional>
#include <iostream>
#include <string>

class heartbeat {
private:
    websocketpp::lib::asio::io_context &io_context_;
    asio::steady_timer timer_;
    std::function<void()> callback_;
    std::chrono::milliseconds interval_;
    std::atomic<bool> stop_requested_;

public:
    heartbeat(websocketpp::lib::asio::io_context &io_context, std::chrono::milliseconds interval, const std::function<void()> &callback)
        : io_context_(io_context),
          timer_(io_context, interval),// Initialize the timer with the interval
          callback_(callback),
          interval_(interval),
          stop_requested_(false) {
        // No need to create a separate thread for io_context.run(), it's already running
        start_timer();
    }

    // Deleted the default constructor to prevent uninitialized usage
    heartbeat() = delete;

    ~heartbeat() {
        stop();
    }

    void start_timer() {
        if (stop_requested_) {
            return;// Check if stopping is requested
        }

        timer_.expires_after(interval_);
        timer_.async_wait([this](const asio::error_code &error) {
            if (!error) {
                // Call the callback function
                callback_();
                // Restart the timer
                start_timer();
            } else if (error != asio::error::operation_aborted) {
                // Handle other errors here
                std::cerr << "Timer Error: " << error.message() << std::endl;
            }
        });
    }

    void stop() {
        stop_requested_ = true;
        timer_.cancel();// Cancel the timer
        // No need to stop the io_context as it's managed externally
    }
};

#endif// DISCORDLITE_HEARTBEAT_H
