//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_PING_SLASH_COMMAND_H
#define DISCORDLITE_PING_SLASH_COMMAND_H

#include <curl/curl.h>
#include <iostream>
#include <string>

void ping_slash_command_response(const std::string &interaction_id, const std::string &interaction_token) {
    CURL *curl = curl_easy_init();
    if (curl) {
        std::string url = "https://discord.com/api/v10/interactions/" + interaction_id + "/" + interaction_token + "/callback";
        std::string json = R"({"type": 4,"data": {"content": "Pong!"}})";

        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
}

#endif//DISCORDLITE_PING_SLASH_COMMAND_H
