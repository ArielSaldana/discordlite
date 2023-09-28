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
        src/websocket_client.cpp)
target_include_directories(discordlite
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${OPENSSL_INCLUDE_DIR}
        ${RapidJSON_INCLUDE_DIRS}
)
target_link_libraries(discordlite
        PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
        asio::asio
)

# If you're not including Boost, ensure that you're using standalone Asio with websocketpp
target_compile_definitions(discordlite
        PUBLIC
        ASIO_STANDALONE
)

# Add test-bot
add_subdirectory(test-bot)
target_link_libraries(test_bot PUBLIC discordlite)
