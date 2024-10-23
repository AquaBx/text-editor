#include "TextEditor.h"

#include <iostream>
#include <ostream>

#include "../Command/CopyCommand/CopyCommand.h"
#include "../Command/CutCommand/CutCommand.h"
#include "../Command/DeleteTextCommand/DeleteTextCommand.h"
#include "../Command/EnterCharCommand/EnterCharCommand.h"
#include "../Command/MoveCursorCommand/MoveCursorCommand.h"
#include "../Command/PasteCommand/PasteCommand.h"

TextEditor::TextEditor() = default;

std::string TextEditor::getTextBuffer()
{
    return textBuffer;
}

void TextEditor::setTextBuffer(std::string t)
{
    textBuffer = t;
}

std::string TextEditor::getClipboard()
{
    return clipboard;
}

void TextEditor::setClipboard(std::string c)
{
    clipboard = c;
}

unsigned long long TextEditor::getPosition() const
{
    return position;
}

void TextEditor::setPosition(const unsigned long long p)
{
    position = p;
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
    renderer.drawText(textBuffer, selectionStart, selectionEnd);
}

void TextEditor::setCommand(Command* cmd)
{
    this->command = cmd;
}

void TextEditor::executeCommand()
{
}

void TextEditor::keyPressed(const bool ctrl, const bool alt, const bool shift, const SDL_KeyCode key)
{
    if ((key == SDLK_BACKSPACE || key == SDLK_DELETE) && selectionStart != selectionEnd)
    {
        DeleteTextCommand(*this, selectionStart, selectionEnd).execute();
    }
    else if (key == SDLK_BACKSPACE)
    {
        DeleteTextCommand(*this, selectionStart - 1, selectionStart).execute();
    }
    else if (key == SDLK_DELETE)
    {
        DeleteTextCommand(*this, selectionStart, selectionStart + 1).execute();
    }
    else if (key == SDLK_RETURN)
    {
        EnterCharCommand(*this, selectionStart, selectionEnd, '\n').execute();
    }
    else if (ctrl)
    {
        switch (key)
        {
        case SDLK_c:
            CopyCommand(*this, selectionStart, selectionEnd).execute();
            break;
        case SDLK_v:
            PasteCommand(*this, selectionStart, selectionEnd).execute();
            break;
        case SDLK_x:
            CutCommand(*this, selectionStart, selectionEnd).execute();
            break;
        case SDLK_a:
            MoveCursorCommand(*this, 0, textBuffer.length()).execute();
            std::cout << textBuffer << std::endl;
            std::cout << selectionStart << std::endl;
            std::cout << selectionEnd << std::endl;
            position = 0;
            break;
        default: ;
        }
    }
    else
    {
        switch (key)
        {
        case (SDLK_UP):
            MoveCursorCommand(*this, 0, 0).execute();
            position = 0;
            break;
        case (SDLK_DOWN):
            MoveCursorCommand(*this, textBuffer.length(), textBuffer.length()).execute();
            position = textBuffer.length();
            break;
        case (SDLK_LEFT):
            if (selectionStart > 0) {
                if (shift) {
                    if (position == selectionStart) {
                        MoveCursorCommand(*this, selectionStart - 1, selectionEnd).execute();
                        position = selectionStart;
                    } else if (position == selectionEnd) {
                        MoveCursorCommand(*this, selectionStart, selectionEnd - 1).execute();
                        position = selectionEnd;
                    }
                } else {
                    MoveCursorCommand(*this, selectionStart - 1, selectionStart - 1).execute();
                    position = selectionStart;
                }
            }
            break;
        case (SDLK_RIGHT):
            if (selectionEnd < textBuffer.length()) {
                if (shift) {
                    if (position == selectionEnd) {
                        MoveCursorCommand(*this, selectionStart, selectionEnd + 1).execute();
                        position = selectionEnd;
                    }
                    else if (position == selectionStart) {
                        MoveCursorCommand(*this, selectionStart + 1, selectionEnd).execute();
                        position = selectionStart;
                    }
                } else {
                    MoveCursorCommand(*this, selectionEnd + 1, selectionEnd + 1).execute();
                    position = selectionEnd;
                }
            }
            break;
        default: ;
        }
    }
}


void TextEditor::keyPressed(const bool ctrl, const bool alt, const bool shift, const char key)
{
    EnterCharCommand(*this, selectionStart, selectionEnd, key).execute();
}

void TextEditor::undoCommand()
{
    // pour V2 ça non ???
}

TextEditor::~TextEditor() = default;
