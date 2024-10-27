#pragma once

#include <string>
#include "../Renderer/Renderer.h"

class Command; // sera override par l'interface Command.h, surtout ne pas importer Command.h sinon on importe en boucle

class TextEditor
{
    friend class CopyCommand;
    friend class CutCommand;
    friend class DeleteTextCommand;
    friend class EnterCharCommand;
    friend class MoveCursorCommand;
    friend class PasteCommand;
    friend class ZoomEditorCommand;

    Command* command = nullptr;
    std::string textBuffer;
    std::string clipboard;
    std::size_t position = 0;
    std::size_t selectionStart = 0;
    std::size_t selectionEnd = 0;
    float fontScale = 1.0f;

public:
    std::string getTextBuffer();
    std::string getClipboard();
    std::size_t getPosition() const;
    std::size_t getSelectionStart() const;
    std::size_t getSelectionEnd() const;

    float getFontScale() const;
    void setTextBuffer(std::string t);
    void setClipboard(std::string c);
    void setPosition(std::size_t p);
    void setSelectionStart(std::size_t start);
    void setSelectionEnd(std::size_t end);
    void setFontScale(float font_scale);

    void draw(const Renderer& renderer) const;
    void setCommand(Command* cmd);
    void keyPressed(bool ctrl, bool alt, bool shift, char key);
    void keyPressed(bool ctrl, bool alt, bool shift, SDL_KeyCode key);
    void executeCommand();
    void undoCommand();
    ~TextEditor();
    TextEditor();
};