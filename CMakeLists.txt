cmake_minimum_required(VERSION 3.16)
project(Fractale)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 QUIET)

if(NOT SDL2_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-2.32.0
    )

    FetchContent_MakeAvailable(SDL2)
endif()

add_executable(${PROJECT_NAME}
    src/main.c
    src/Functions.c
)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2 m)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)