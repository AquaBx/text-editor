cmake_minimum_required(VERSION 3.29)
project(TextEditor)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 26)

add_subdirectory(libs/SDL)
include_directories(libs/SDL/include)

add_subdirectory(libs/SDL_ttf)
include_directories(libs/SDL_ttf)

add_executable(TextEditor WIN32 main.cpp
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Command/Command.h
        src/Command/CopyCommand/CopyCommand.h
        src/Command/CopyCommand/CopyCommand.cpp
        src/Command/CutCommand/CutCommand.h
        src/Command/CutCommand/CutCommand.cpp
        src/Command/DeleteTextCommand/DeleteTextCommand.h
        src/Command/DeleteTextCommand/DeleteTextCommand.cpp
        src/Command/EnterCharCommand/EnterCharCommand.h
        src/Command/EnterCharCommand/EnterCharCommand.cpp
        src/Command/MoveCursorCommand/MoveCursorCommand.h
        src/Command/MoveCursorCommand/MoveCursorCommand.cpp
        src/Command/PasteCommand/PasteCommand.h
        src/Command/PasteCommand/PasteCommand.cpp
        src/Client/Client.h
        src/Client/Client.cpp
        src/TextEditor/TextEditor.h
        src/TextEditor/TextEditor.cpp)
target_link_libraries(TextEditor SDL2 SDL2_ttf)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)