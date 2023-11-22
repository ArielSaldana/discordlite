//
// Created by Ariel Saldana on 10/26/23.
//

#include "message_create_handler.h"
#include "http-client/send_message.h"
#include "protocol/events/dispatch_event.h"
#include <random>
#include <string_view>
#include <vector>

// Get the GLaDOS quotes
std::vector<std::string_view> glados_quotes() {
    std::vector<std::string_view> quotes{
            "Place The Device Of The Ground Then Lie On Your Stomach With Your Arms At Your Sides. A Party Associate Will Arrive Shortly To Collect You For Your Party.",
            "In Fact, You Did So Well I’m Going To Note This On Your File In the Commendations Section. Oh, There’s Lots Of Room Here.",
            "Let Me Give You The Fast Version [Superfast Inaudible Explanation]. There, If You Have Any Questions, Just Remember What I Said In Slow Motion.",
            "A Bitter, Unlikeable Loner Whose Passing Shall Not Be Mourned. ‘Shall Not Be Mourned.’ That’s Exactly What It Says. Very Formal. Very Official.",
            "I’m Not Angry. Just Go Back To The Testing Area.",
            "Despite Your Violent Behavior, The Only Thing You’ve Managed To Break So Far Is My Heart.",
            "“Remember Before When I Was Talking About Smelly Garbage Standing Around Being Useless? That Was A Metaphor. I Was Actually Talking About You.”",
            "“I Wouldn’t Bother With That Thing. My Guess Is That Touching it Will Just Make Your Life Even Worse Somehow”",
            "It’s Right Here In Your File: On Other People, It Looks Fine. But Right Here A Scientist Has Noted That On You It Looks Stupid”",
            "Any Feelings You Think It Has For You Are Simply By-Products Of Your Sad, Empty Life.",
            "Here Come The Test Results: 'You Are A Horrible Person.' That’s What It Says, 'A Horrible Person.' We Weren’t Even Testing For That.",
            "Remember When The Platform Was Sliding Into The Fire Pit, And I Said 'Goodbye,' And You Were Like 'No Way!' And Then I Was All, 'We Pretended We Were Going To Murder You.' That Was Great.",
            "It Made Shoes For Orphans. Nice Job Breaking It. Hero.",
            "The Birth Parents You Are Trying To Reach Do Not Love You.",
            "Don’t Believe Me? Here, I’ll Put You on: [Hellooo!] That’s You! That’s How Dumb You Sound.",
            "Nobody But You Is That Pointlessly Cruel.",
            "If You Become Light Headed From Thirst, Feel Free To Pass Out.",
            "How Are You Holding Up? Because I’m A Potato.",
            "You look great, by the way. Very healthy.",
            "This next test involves turrets. You remember them, right? They're the pale spherical things that are full of bullets. Oh wait. That's you in five seconds. Good luck.",
            "Agh! Bird! Bird! Kill it! It's evil!",
            "Say, you're good at murder. Could you - ow - murder this bird for me?",
            "I'm sorry. You didn't react at the time, so I was worried it sailed right over your head. Which would have made this apology seem insane. That's why I had to call you garbage a second time just now."};
    return quotes;
}

void message_create_handler::process(discord_client_state &client_state, const dispatch_event &event) const {
    if (event.getAuthor()->getId() != "1156420471013777580" && event.getContent().value().contains("manboober")) {
        const std::vector<std::string_view> &quotes = glados_quotes();

        // Create a random device and generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Create a distribution from 0 to the number of quotes - 1
        std::uniform_int_distribution<> distrib(0, quotes.size() - 1);

        // Get a random index
        int random_index = distrib(gen);

        // Select the quote at the random index
        std::string_view random_quote = quotes[random_index];

        // Send the message
        send_message(event.getChannelId().value(), std::string(random_quote), client_state.get_bot_token());
    }
}
