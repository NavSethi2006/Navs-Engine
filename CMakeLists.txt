cmake_minimum_required(VERSION 3.16)
project(navsengine LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL3


# Add source files
file(GLOB SOURCES src/*.c)
file (GLOB ASSETS src/assets/*.c)
file(GLOB UTILS src/utils/*.c)


add_executable(navsengine ${SOURCES} ${ASSETS} ${UTILS})

# Include SDL3 headers
target_include_directories(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/include/)

# Platform-specific settings
if (WIN32)

target_link_libraries(navsengine PUBLIC
${CMAKE_SOURCE_DIR}/lib/win/libtmx.a
${CMAKE_SOURCE_DIR}/lib/win/libxml2.a
${CMAKE_SOURCE_DIR}/lib/win/libzlibstatic.a
)

  
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/win/libSDL3.a)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/win/libSDL3_image.a)
    

elseif (UNIX)
    
    find_package(LibXml2 REQUIRED)
    find_package(ZLIB REQUIRED)
    
    target_link_libraries(navsengine PUBLIC LibXml2::LibXml2 ZLIB::ZLIB)
    target_link_libraries(navsengine PUBLIC m)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/gnu/libSDL3.so)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/gnu/libSDL3_image.so)
    target_link_libraries(navsengine PUBLIC ${CMAKE_SOURCE_DIR}/lib/gnu/libtmx.a)

endif()