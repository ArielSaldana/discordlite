//
// Created by Ariel Saldana on 10/27/23.
//

#ifndef DISCORDLITE_GET_GATEWAY_BOT_API_H
#define DISCORDLITE_GET_GATEWAY_BOT_API_H

#include <curl/curl.h>
#include <string>
#include <iostream>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

std::string get_gateway_bot(const std::string &token) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string result;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::string url = "https://discord.com/api/v10/gateway/bot";
        std::string authHeader = "Authorization: Bot " + token;

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());
        if (!headers) {
            std::cerr << "Failed to append Authorization header\n";
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return result;
        }

        headers = curl_slist_append(headers, "Content-Type: application/json");
        if (!headers) {
            std::cerr << "Failed to append Content-Type header\n";
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return result;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            result = readBuffer;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize curl\n";
    }

    curl_global_cleanup();
    return result;
}

#endif//DISCORDLITE_GET_GATEWAY_BOT_API_H
