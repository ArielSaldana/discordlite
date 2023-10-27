//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_SEND_MESSAGE_H
#define DISCORDLITE_SEND_MESSAGE_H

#include <curl/curl.h>
#include <string>

void send_message(const std::string &channel_id, const std::string &message, const std::string &token) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::string url = "https://discord.com/api/v10/channels/" + channel_id + "/messages";
        std::string json = R"({"content": ")" + message + R"(", "tts": false})";

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bot " + token).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}


#endif//DISCORDLITE_SEND_MESSAGE_H
