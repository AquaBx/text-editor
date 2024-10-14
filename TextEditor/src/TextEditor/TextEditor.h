#pragma once

#include <string>
#include "../Command/Command.h"
#include "../Renderer/Renderer.h"

class TextEditor {
private:
    Command * command = nullptr;
    std::string textBuffer = "test";
    std::string clipboard = "";
    int selectionStart = 0;
    int selectionEnd = 0;
public : 
    void draw(Renderer renderer);
    void setCommand(Command * cmd);
    void keyPressed(bool ctrl, bool alt, SDL_KeyCode key);
    void executeCommand();
    void undoCommand();
    ~TextEditor();
    TextEditor();
};