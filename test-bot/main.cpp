//
// Created by Ariel Saldana on 9/27/23.
//
#include "client/websocket_client.h"
#include "library.h"
#include "client/discord_client.h"

int main() {
    hello();
    discord_client client("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
}
