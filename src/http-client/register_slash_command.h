//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_REGISTER_SLASH_COMMAND_H
#define DISCORDLITE_REGISTER_SLASH_COMMAND_H

#include "get_gateway_bot_api.h"
#include <curl/curl.h>
#include <iostream>
#include <string>

void register_slash_command(const std::string &token, const std::string &application_id, const std::string &guild_id) {
    CURL *curl = curl_easy_init();
    if (curl) {
        std::string url = "https://discord.com/api/v10/applications/" + application_id + "/guilds/" + guild_id + "/commands";
        std::string json = R"({"name":"bong","type":1,"description":"A simple bing bong command"})";
        std::string response_string;

        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bot " + token).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            std::cout << "Response from " << url << ": " << response_string << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}

#endif//DISCORDLITE_REGISTER_SLASH_COMMAND_H
