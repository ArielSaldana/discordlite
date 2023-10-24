//
// Created by Ariel Saldana on 9/27/23.
//
#include "client/discord_client.hpp"
#include "client/websocket_client.hpp"
#include "library.h"

int main() {
    hello();
    discord_client client("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
}
