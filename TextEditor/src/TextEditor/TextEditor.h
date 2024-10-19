#pragma once

#include <string>
#include "../Renderer/Renderer.h"
#include "../Command/Command.h"

class TextEditor
{
    Command* command = nullptr;
    std::string textBuffer;
    std::string clipboard;
    unsigned long long selectionStart = 0;
    unsigned long long selectionEnd = 0;
    int lineLength = 50; // voir si y'a pas mieux
public :
    void draw(const Renderer& renderer) const;
    std::string getTextBuffer();
    void setTextBuffer(std::string t);
    std::string getClipboard();
    void setClipboard(std::string c);
    unsigned long long getSelectionStart() const;
    void setSelectionStart(unsigned long long start);
    unsigned long long getSelectionEnd() const;
    void setSelectionEnd(unsigned long long end);
    void setCommand(Command* cmd);
    void keyPressed(const bool ctrl, const bool alt, const bool shift, const char key);
    void keyPressed(const bool ctrl, const bool alt, const bool shift, const SDL_KeyCode key);
    void executeCommand();
    void undoCommand();
    ~TextEditor();
    TextEditor();
};
