//
// Created by Ariel Saldana on 9/29/23.
//

#ifndef DISCORDLITE_MESSAGE_H
#define DISCORDLITE_MESSAGE_H

#include "rapidjson/document.h"

struct message {
private:
    int opcode;
    rapidjson::Document doc;
public:
    explicit message(int _opcode, rapidjson::Document _document);
    [[nodiscard]] int get_opcode() const;
    rapidjson::Document * get_json_document();
};

#endif//DISCORDLITE_MESSAGE_H
