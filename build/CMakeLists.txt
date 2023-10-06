cmake_minimum_required(VERSION 3.10)

project(PainterIO)

# Set up Google Test
enable_testing()
add_subdirectory(googletest)  # Assumes the Google Test source is in a directory named 'googletest'
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Include your headers
include_directories(Headers)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Define your source and header files (assuming they're directly inside the respective directories)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "Headers/*.h")

# EasyBotTest (you can replicate this for MediumBotTest, HardBotTest, etc.)
add_executable(EasyBotTest testing/test-EasyBot.cpp ${SOURCES} ${HEADERS})

# Link against GoogleTest and SFML
target_link_libraries(EasyBotTest gtest gtest_main sfml-graphics)

add_test(NAME EasyBotTest COMMAND EasyBotTest)
