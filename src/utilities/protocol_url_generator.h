//
// Created by Ariel Saldana on 10/30/23.
//

#ifndef DISCORDLITE_PROTOCOL_URL_GENERATOR_H
#define DISCORDLITE_PROTOCOL_URL_GENERATOR_H

#include <iostream>
#include <string>

class protocol_url_generator {
public:
    static std::string generate_url(const std::string &websocket_address, const std::string &protocol_version, const std::string &protocol_format);
};


#endif//DISCORDLITE_PROTOCOL_URL_GENERATOR_H
