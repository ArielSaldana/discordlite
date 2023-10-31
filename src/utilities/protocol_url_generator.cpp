//
// Created by Ariel Saldana on 10/30/23.
//

#include "protocol_url_generator.h"

std::string protocol_url_generator::generate_url(const std::string &websocket_address, const std::string &protocol_version, const std::string &protocol_format) {
    return websocket_address + "/?v=" + protocol_version + "&encoding=" + protocol_format;
}
