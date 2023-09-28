//
// Created by Ariel Saldana on 9/27/23.
//
#include "library.h"
#include "websocket_client.h"

int main() {
    hello();
    auto* client = new WebsocketClient("wss://gateway.discord.gg/?v=10&encoding=json", "gateway.discord.gg");
    client->connect();
}
