#pragma once

#include <string>
#include "../Renderer/Renderer.h"
#include "../Command/Command.h"

class TextEditor {
private:
    Command * command = nullptr;
    std::string textBuffer;
    std::string clipboard;
    int selectionStart = 0;
    int selectionEnd = 0;
    int lineLength = 50; // voir si y'a pas mieux
public : 
    void draw(Renderer& renderer);
    std::string getTextBuffer();
    void setTextBuffer(std::string t);
    std::string getClipboard();
    void setClipboard(std::string c);
    int getSelectionStart();
    void setSelectionStart(int start);
    int getSelectionEnd();
    void setSelectionEnd(int end);
    void setCommand(Command * cmd);
    void keyPressed(bool ctrl, bool alt, bool shift, SDL_KeyCode key);
    void executeCommand();
    void undoCommand();
    ~TextEditor();
    TextEditor();
};