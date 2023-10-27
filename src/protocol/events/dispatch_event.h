//
// Created by Ariel Saldana on 10/25/23.
//

#ifndef DISCORDLITE_DISPATCH_EVENT_H
#define DISCORDLITE_DISPATCH_EVENT_H

#include "protocol/deserializable.h"
#include "protocol/gateway_event_payload.h"
#include <iostream>
#include <optional>
#include "protocol/events/author.h"

struct dispatch_event : public gateway_event_payload, public deserializable {
    std::optional<std::string> guild_id_;
    std::optional<std::string> content_;
    const std::optional<author> &getAuthor() const;
    std::optional<std::string> channel_id_;
    std::optional<author> author_;

    const std::optional<std::string> &getChannelId() const;
    [[nodiscard]] const std::optional<std::string> &getGuildId() const;
    [[nodiscard]] const std::optional<std::string> &getContent() const;
    void deserialize(const rapidjson::Value &value) override;
};

#endif//DISCORDLITE_DISPATCH_EVENT_H
