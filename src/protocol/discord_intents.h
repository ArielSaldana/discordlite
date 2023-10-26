//
// Created by Ariel Saldana on 10/22/23.
//

#ifndef DISCORDLITE_DISCORD_INTENTS_H
#define DISCORDLITE_DISCORD_INTENTS_H

#include <bitset>

class discord_intents {
public:
    static const discord_intents GUILDS;
    static const discord_intents GUILD_MEMBERS;
    static const discord_intents GUILD_MODERATION;
    static const discord_intents GUILD_EMOJIS_AND_STICKERS;
    static const discord_intents GUILD_INTEGRATIONS;
    static const discord_intents GUILD_WEBHOOKS;
    static const discord_intents GUILD_INVITES;
    static const discord_intents GUILD_VOICE_STATES;
    static const discord_intents GUILD_PRESENCES;
    static const discord_intents GUILD_MESSAGES;
    static const discord_intents GUILD_MESSAGE_REACTIONS;
    static const discord_intents GUILD_MESSAGE_TYPING;
    static const discord_intents DIRECT_MESSAGES;
    static const discord_intents DIRECT_MESSAGE_REACTIONS;
    static const discord_intents DIRECT_MESSAGE_TYPING;
    static const discord_intents MESSAGE_CONTENT;
    static const discord_intents GUILD_SCHEDULED_EVENTS;
    static const discord_intents AUTO_MODERATION_CONFIGURATION;
    static const discord_intents AUTO_MODERATION_EXECUTION;

    explicit discord_intents(int value);

    [[nodiscard]] int value() const;

    [[nodiscard]] std::bitset<32> bitset() const;

    discord_intents(std::initializer_list<discord_intents> list);

    discord_intents operator|(const discord_intents &other) const {
        return discord_intents(value_ | other.value_);
    }

private:
    int value_;
};


#endif//DISCORDLITE_DISCORD_INTENTS_H
