cmake_minimum_required(VERSION 3.16)
project(navsengine LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL3

find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)

# Add source files
file(GLOB SOURCES src/*.c)
file (GLOB ASSETS src/assets/*.c)
file(GLOB UTILS src/utils/*.c)
file(GLOB TMX src/tmx/*.c)



add_executable(navsengine ${SOURCES} ${ASSETS} ${UTILS} ${TMX})

# Include SDL3 headers
target_include_directories(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/include/)
target_link_libraries(navsengine PUBLIC LibXml2::LibXml2)

target_link_libraries(navsengine PUBLIC ZLIB::ZLIB)

# Platform-specific settings
if (WIN32)
    # Windows-specific options (if needed)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/win/libSDL3.a)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/win/libSDL3_image.a)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/win/libtmx.a)

elseif (UNIX)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/gnu/libSDL3.so)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/gnu/libSDL3_image.so)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/gnu/libtmx.a)

endif()