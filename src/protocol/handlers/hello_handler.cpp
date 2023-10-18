//
// Created by Ariel Saldana on 10/17/23.
//

#include "hello_handler.h"
#include "iostream"

void hello_handler::process(const HelloEvent &payload) {
    std::cout << payload.heartbeat_interval << std::endl;
}
