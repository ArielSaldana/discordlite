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
    if (value.HasMember("session_id") && value["session_id"].IsString()) {
        session_id_ = value["session_id"].GetString();
    }
    if (value.HasMember("session_type") && value["session_type"].IsString()) {
        session_type_ = value["session_type"].GetString();
    }
    if (value.HasMember("resume_gateway_url") && value["resume_gateway_url"].IsString()) {
        resume_gateway_url_ = value["resume_gateway_url"].GetString();
    }
}
auto dispatch_event::getGuildId() const -> const std::optional<std::string> & {
    return guild_id_;
}
auto dispatch_event::getContent() const -> const std::optional<std::string> & {
    return content_;
}
auto dispatch_event::getChannelId() const -> const std::optional<std::string> & {
    return channel_id_;
}
auto dispatch_event::getAuthor() const -> const std::optional<author> & {
    return author_;
}
auto dispatch_event::getToken() const -> const std::optional<std::string> & {
    return token_;
}
auto dispatch_event::getId() const -> const std::optional<std::string> & {
    return id_;
}
auto dispatch_event::getType() const -> const std::optional<int> & {
    return type_;
}
auto dispatch_event::get_resume_url() const -> const std::optional<std::string> & {
    return resume_gateway_url_;
}
