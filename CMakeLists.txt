cmake_minimum_required(VERSION 3.15)

project(snake-game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

add_subdirectory(lib/raylib)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")
