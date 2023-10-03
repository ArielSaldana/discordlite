//
// Created by Ariel Saldana on 9/29/23.
//

#include "message.h"

message::message(int _opcode, rapidjson::Document _document)
    : opcode(_opcode), doc(std::move(_document)) { }

int message::get_opcode() const {
    return opcode;
}

rapidjson::Document * message::get_json_document() {
    return &doc;
}
