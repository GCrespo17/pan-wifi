cmake_minimum_required(VERSION 3.21)

project(WifiTui C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.c
    src/WifiController.c
    src/WifiList.c
)

set(HEADERS
    include/WifiController.h
    include/WifiList.h
    include/WifiData.h
)

include_directories(include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
