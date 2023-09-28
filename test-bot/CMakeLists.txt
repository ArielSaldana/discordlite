cmake_minimum_required(VERSION 3.26)
project(test_bot)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(test_bot main.cpp)
target_link_libraries(test_bot PUBLIC discordlite PRIVATE ${OPENSSL_CRYPTO_LIBRARY} PRIVATE ${OPENSSL_SSL_LIBRARY})
