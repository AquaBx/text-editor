#include "TextEditor.h"

#include "../Command/CopyCommand/CopyCommand.h"
#include "../Command/CutCommand/CutCommand.h"
#include "../Command/DeleteTextCommand/DeleteTextCommand.h"
#include "../Command/EnterCharCommand/EnterCharCommand.h"
#include "../Command/MoveCursorCommand/MoveCursorCommand.h"
#include "../Command/PasteCommand/PasteCommand.h"

TextEditor::TextEditor() = default;

std::string TextEditor::getTextBuffer() {
    return textBuffer;
}

void TextEditor::setTextBuffer(std::string t) {
    textBuffer = t;
}

std::string TextEditor::getClipboard() {
    return clipboard;
}

void TextEditor::setClipboard(std::string c) {
    clipboard = c;
}

unsigned long long TextEditor::getSelectionStart() const
{
    return selectionStart;
}

void TextEditor::setSelectionStart(const unsigned long long start)
{
    selectionStart = start;
}

unsigned long long TextEditor::getSelectionEnd() const
{
    return selectionEnd;
}

void TextEditor::setSelectionEnd(const unsigned long long end)
{
    selectionEnd = end;
}

void TextEditor::draw(const Renderer& renderer) const
{
    renderer.drawText(textBuffer);
}

void TextEditor::setCommand(Command *cmd) {
    this->command = cmd;
}

void TextEditor::executeCommand() {

}

void TextEditor::keyPressed(const bool ctrl, const bool alt, const bool shift, const SDL_KeyCode key)
{
    if ((key == SDLK_BACKSPACE || key == SDLK_DELETE) && selectionStart != selectionEnd)
    {
        DeleteTextCommand(*this, selectionStart, selectionEnd).execute();
        return;
    }
    else if (key == SDLK_BACKSPACE)
    {
        // vérifier que start - 1 >= 0
        DeleteTextCommand(*this, selectionStart - 1, selectionStart).execute();
        return;
    }
    else if (key == SDLK_DELETE)
    {
        // vérifier que start + 1 < len
        DeleteTextCommand(*this, selectionStart, selectionStart + 1).execute();
        return;
    }

    switch (ctrl) {
        case true:
            switch (key) {
                case SDLK_c:
                CopyCommand(*this, selectionStart, selectionEnd).execute();
                return;
                case SDLK_v:
                PasteCommand(*this, selectionStart, selectionEnd).execute();
                return;
                case SDLK_x:
                CutCommand(*this, selectionStart, selectionEnd).execute();
                return;
                case SDLK_a:
                MoveCursorCommand(*this, 0, textBuffer.length() - 1).execute();
                return;
            default:
                    return;
            }
        case false:
            switch (alt) {
                case true:
                    switch (key) {
                        case (SDLK_UP):
                        MoveCursorCommand(*this, selectionStart, selectionEnd - lineLength).execute();
                        return;
                    case (SDLK_DOWN):
                            MoveCursorCommand(*this, selectionStart, selectionEnd + lineLength).execute();
                        return;
                    case (SDLK_LEFT):
                            MoveCursorCommand(*this, selectionStart, selectionEnd - 1).execute();
                        return;
                    case (SDLK_RIGHT):
                            MoveCursorCommand(*this, selectionStart, selectionEnd + 1).execute();
                        return;
                    default:
                        return;
                    }
                case false:
                    switch (key) {
                        case (SDLK_UP):
                        case (SDLK_DOWN):
                        case (SDLK_LEFT):
                        case (SDLK_RIGHT):
                        case (SDLK_UNKNOWN):
                        return;
                    default:
                        EnterCharCommand(*this,selectionStart, selectionEnd, key).execute();
                        return;
                    }
            }
    }
}

void TextEditor::undoCommand() {
    // pour V2 ça non ???
}

TextEditor::~TextEditor() = default;
