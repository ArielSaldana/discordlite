//
// Created by Ariel Saldana on 10/25/23.
//

#include "protocol/discord_intents.h"

const discord_intents discord_intents::GUILDS(1 << 0);
const discord_intents discord_intents::GUILD_MEMBERS(1 << 1);
const discord_intents discord_intents::GUILD_MODERATION(1 << 2);
const discord_intents discord_intents::GUILD_EMOJIS_AND_STICKERS(1 << 3);
const discord_intents discord_intents::GUILD_INTEGRATIONS(1 << 4);
const discord_intents discord_intents::GUILD_WEBHOOKS(1 << 5);
const discord_intents discord_intents::GUILD_INVITES(1 << 6);
const discord_intents discord_intents::GUILD_VOICE_STATES(1 << 7);
const discord_intents discord_intents::GUILD_PRESENCES(1 << 8);
const discord_intents discord_intents::GUILD_MESSAGES(1 << 9);
const discord_intents discord_intents::GUILD_MESSAGE_REACTIONS(1 << 10);
const discord_intents discord_intents::GUILD_MESSAGE_TYPING(1 << 11);
const discord_intents discord_intents::DIRECT_MESSAGES(1 << 12);
const discord_intents discord_intents::DIRECT_MESSAGE_REACTIONS(1 << 13);
const discord_intents discord_intents::DIRECT_MESSAGE_TYPING(1 << 14);
const discord_intents discord_intents::MESSAGE_CONTENT(1 << 15);
const discord_intents discord_intents::GUILD_SCHEDULED_EVENTS(1 << 16);
const discord_intents discord_intents::AUTO_MODERATION_CONFIGURATION(1 << 20);
const discord_intents discord_intents::AUTO_MODERATION_EXECUTION(1 << 21);

discord_intents::discord_intents(int value) : value_(value) {}

int discord_intents::value() const { return value_; }

std::bitset<32> discord_intents::bitset() const {
    return std::bitset<32>(value_);
}

discord_intents::discord_intents(std::initializer_list<discord_intents> list) {
    value_ = 0;
    for (const auto &intent: list) {
        value_ |= intent.value_;
    }
}
