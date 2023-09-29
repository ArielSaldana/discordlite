cmake_minimum_required(VERSION 3.26)
project(discordlite)

set(CMAKE_CXX_STANDARD 23)

# OpenSSL
find_package(OpenSSL REQUIRED)

# RapidJSON
find_package(RapidJSON CONFIG REQUIRED)

find_package(asio CONFIG REQUIRED)

# Websocketpp
find_package(websocketpp CONFIG REQUIRED)

# Create discordlite library
add_library(discordlite src/library.cpp
        src/client/websocket_client.cpp
        src/client/discord_client.cpp
        src/client/discord_client.h
        src/client/websocket_client.h)
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
)

if(WIN32)
    target_link_libraries(discordlite PUBLIC ws2_32)
endif()

# If you're not including Boost, ensure that you're using standalone Asio with websocketpp
target_compile_definitions(discordlite
        PUBLIC
#        ASIO_STANDALONE
#        _WEBSOCKETPP_CPP11_THREAD_
#        WEBSOCKETPP_BOOST_LIB_FREE
        WEBSOCKETPP_NO_CPP11_SYSTEM_ERROR # Required if Boost system_error isn't available
)

# Add test-bot
add_subdirectory(test-bot)
target_link_libraries(test_bot PUBLIC discordlite)
