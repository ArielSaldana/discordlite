//
// Created by Ariel Saldana on 9/27/23.
//
#include "client/discord_client.hpp"
#include "protocol/discord_intents.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main() {
    if (const char *bot_token = std::getenv("BOT_TOKEN")) {
        const std::string token = bot_token;// Convert to std::string for ease of use
        const discord_intents combined_intents = {
                discord_intents::GUILDS,
                discord_intents::GUILD_MEMBERS,
                discord_intents::GUILD_MESSAGES,
                discord_intents::MESSAGE_CONTENT,
                discord_intents::AUTO_MODERATION_EXECUTION};
        discord_client client(token, combined_intents);

        // other bot api shit

        /*
         *  discord_client.on_guild_message(int guild_id, std::string msg)
         *  discord_client.on_guild_join(int guild_id, const discord_user &user)
         */

    } else {
        std::cout << "Environment variable BOT_TOKEN is not set." << std::endl;
    }
    return 0;
}

