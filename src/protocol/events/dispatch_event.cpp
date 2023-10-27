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
    if (value.HasMember("id") && value["id"].IsString()) {
        id_ = value["id"].GetString();
    }

    if (value.HasMember("token") && value["token"].IsString()) {
        token_ = value["token"].GetString();
    }

    if (value.HasMember("type") && value["type"].IsInt()) {
        type_ = value["type"].GetInt();
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
const std::optional<std::string> &dispatch_event::getToken() const {
    return token_;
}
const std::optional<std::string> &dispatch_event::getId() const {
    return id_;
}
const std::optional<int> &dispatch_event::getType() const {
    return type_;
}
