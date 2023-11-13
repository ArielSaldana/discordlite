//
// Created by Ariel Saldana on 10/25/23.
//

#ifndef DISCORDLITE_DISPATCH_EVENT_H
#define DISCORDLITE_DISPATCH_EVENT_H

#include "protocol/deserializable.h"
#include "protocol/events/author.h"
#include "protocol/gateway_event_payload.h"
#include <iostream>
#include <optional>

struct dispatch_event : public gateway_event_payload, public deserializable {
private:
    std::optional<std::string> guild_id_;
    std::optional<std::string> content_;
    std::optional<std::string> channel_id_;
    std::optional<author> author_;
    std::optional<std::string> token_;
    std::optional<std::string> id_;
    std::optional<int> type_;
    // ready event
    std::optional<std::string> session_id_;
    std::optional<std::string> session_type_;
    std::optional<std::string> resume_gateway_url_;

public:
    [[nodiscard]] auto getChannelId() const -> const std::optional<std::string> &;
    [[nodiscard]] auto getGuildId() const -> const std::optional<std::string> &;
    [[nodiscard]] auto getAuthor() const -> const std::optional<author> &;
    [[nodiscard]] auto getContent() const -> const std::optional<std::string> &;
    [[nodiscard]] auto getToken() const -> const std::optional<std::string> &;
    [[nodiscard]] auto getId() const -> const std::optional<std::string> &;
    [[nodiscard]] auto getType() const -> const std::optional<int> &;
    [[nodiscard]] auto get_resume_url() const -> const std::optional<std::string> &;

    void deserialize(const rapidjson::Value &value) override;
};

#endif//DISCORDLITE_DISPATCH_EVENT_H
