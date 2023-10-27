//
// Created by Ariel Saldana on 10/27/23.
//

#include "dispatch_event.h"

void dispatch_event::deserialize(const rapidjson::Value &value) {
    if (value.HasMember("guild_id") && value["guild_id"].IsString()) {
        guild_id_ = value["guild_id"].GetString();
    }
    if (value.HasMember("content") && value["content"].IsString()) {
        content_ = value["content"].GetString();
    }
    if (value.HasMember("channel_id") && value["channel_id"].IsString()) {
        channel_id_ = value["channel_id"].GetString();
    }
    if (value.HasMember("author") && value["author"].IsObject()) {
        author au;
        au.deserialize(value["author"].GetObject());
        author_ = au;
    }
}
const std::optional<std::string> &dispatch_event::getGuildId() const {
    return guild_id_;
}
const std::optional<std::string> &dispatch_event::getContent() const {
    return content_;
}
const std::optional<std::string> &dispatch_event::getChannelId() const {
    return channel_id_;
}
const std::optional<author> &dispatch_event::getAuthor() const {
    return author_;
}
