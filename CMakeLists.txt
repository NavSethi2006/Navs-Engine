cmake_minimum_required(VERSION 3.16)
project(online_pong LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL3

# Add source files
file(GLOB SOURCES src/*.c)

add_executable(online_pong ${SOURCES})

# Include SDL3 headers
target_include_directories(online_pong PUBLIC ${CMAKE_SOURCE_DIR}/include/)

# Platform-specific settings
if (WIN32)
    # Windows-specific options (if needed)
    target_link_libraries(online_pong PUBLIC ${CMAKE_SOURCE_DIR}/lib/win/libSDL3.a)
elseif (UNIX)
    target_link_libraries(online_pong PUBLIC ${CMAKE_SOURCE_DIR}/lib/gnu/libSDL3.so)
endif()