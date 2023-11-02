cmake_minimum_required(VERSION 3.26)
project(discordlite)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")

#SET (CMAKE_CXX_FLAGS_INIT                "-Wall -std=c++17")
#SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
#SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
#SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
#SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
#option(USE_CLANG "build application with clang" ON)
#
#if(USE_CLANG)
#    SET (...)
#endif(USE_CLANG)



# OpenSSL
find_package(OpenSSL REQUIRED)

# RapidJSON
find_package(RapidJSON CONFIG REQUIRED)

find_package(asio CONFIG REQUIRED)

# Websocketpp
find_package(websocketpp CONFIG REQUIRED)

find_package(CURL CONFIG REQUIRED)

# Create discordlite library
add_library(discordlite src/library.cpp
        src/client/websocket_client.cpp
        src/client/discord_client.cpp
        src/client/discord_client.hpp
        src/client/websocket_client.hpp
        src/protocol/events/gateway_event.h
        src/protocol/deserializable.h
        src/protocol/handlers/hello_handler.cpp
        src/protocol/handlers/hello_handler.h
        src/protocol/handlers/handler.h
        src/protocol/deserializer.cpp
        src/protocol/deserializer.h
        src/protocol/heartbeat.h
        src/protocol/discord_intents.h
        src/client/discord_client_state.cpp
        src/client/discord_client_state.h
        src/protocol/discord_intents.cpp
        src/protocol/handlers/dispatch_handler.cpp
        src/protocol/handlers/dispatch_handler.h
        src/protocol/events/dispatch_event.h
        src/protocol/events/hello_event.cpp
        src/protocol/handlers/event_handler.cpp
        src/protocol/handlers/event_handler.h
        src/protocol/handlers/dispatch/message_create_handler.cpp
        src/protocol/handlers/dispatch/message_create_handler.h
        src/protocol/events/dispatch_event.cpp
        src/http-client/send_message.h
        src/protocol/events/author.h
        src/http-client/register_slash_command.h
        src/http-client/ping_slash_command.h
        src/protocol/handlers/dispatch/interaction_create_handler.cpp
        src/protocol/handlers/dispatch/interaction_create_handler.h
        src/protocol/opcodes.cpp
        src/http-client/get_gateway_bot_api.h
        src/models/gateway_bot.h
        src/models/session_start_limit.h
        src/utilities/protocol_url_generator.cpp
        src/utilities/protocol_url_generator.h)
target_include_directories(discordlite
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${OPENSSL_INCLUDE_DIR}
        ${RapidJSON_INCLUDE_DIRS}
        ${WEBSOCKETPP_INCLUDE_DIR}
)
target_link_libraries(discordlite
        PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
        asio::asio
        CURL::libcurl
)

if (WIN32)
    target_link_libraries(discordlite PUBLIC ws2_32)
endif ()

# If you're not including Boost, ensure that you're using standalone Asio with websocketpp
target_compile_definitions(discordlite
        PUBLIC
        WEBSOCKETPP_STANDALONE_ASIO
                ASIO_STANDALONE
                _WEBSOCKETPP_CPP11_THREAD_
                WEBSOCKETPP_BOOST_LIB_FREE
        WEBSOCKETPP_NO_CPP11_SYSTEM_ERROR # Required if Boost system_error isn't available
)

# Add test-bot
add_subdirectory(test-bot)
target_link_libraries(test_bot PUBLIC discordlite)
