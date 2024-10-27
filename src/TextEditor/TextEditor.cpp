#include "TextEditor.h"

#include <iostream>
#include <ostream>
#include <cctype> 

#include "../Command/CopyCommand/CopyCommand.h"
#include "../Command/CutCommand/CutCommand.h"
#include "../Command/DeleteTextCommand/DeleteTextCommand.h"
#include "../Command/EnterCharCommand/EnterCharCommand.h"
#include "../Command/MoveCursorCommand/MoveCursorCommand.h"
#include "../Command/PasteCommand/PasteCommand.h"
#include "../Command/ZoomEditorCommand/ZoomEditorCommand.h"

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

std::size_t TextEditor::getPosition() const
{
    return position;
}

void TextEditor::setPosition(const std::size_t p)
{
    position = p;
}

std::size_t TextEditor::getSelectionStart() const
{
    return selectionStart;
}

void TextEditor::setSelectionStart(const std::size_t start)
{
    selectionStart = start;
}

std::size_t TextEditor::getSelectionEnd() const
{
    return selectionEnd;
}

void TextEditor::setSelectionEnd(const std::size_t end)
{
    selectionEnd = end;
}

float TextEditor::getFontScale() const
{
    return fontScale;
}

void TextEditor::setFontScale(const float font_scale)
{
    fontScale = font_scale;
}

void TextEditor::draw(const Renderer& renderer) const
{
    renderer.drawText(textBuffer, selectionStart, selectionEnd, fontScale);
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
    else if (key == SDLK_RETURN || key ==  SDLK_KP_ENTER)
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
            MoveCursorCommand(*this,0, 0, textBuffer.length()).execute();
            break;
        case SDLK_KP_MINUS:
            ZoomEditorCommand(*this,-0.25).execute();
            break;
        case SDLK_KP_PLUS:
            ZoomEditorCommand(*this,0.25).execute();
            break;
        default: ;
        }
    }
    else
    {
        switch (key)
        {
        case (SDLK_UP):
            MoveCursorCommand(*this,0, 0, 0).execute();
            break;
        case (SDLK_DOWN):
            MoveCursorCommand(*this,textBuffer.length(), textBuffer.length(), textBuffer.length()).execute();
            break;
        case (SDLK_LEFT):
            if (shift)
            {
                if (position == selectionEnd && selectionStart > 0) {
                    MoveCursorCommand(*this,position, selectionStart - 1, selectionEnd).execute();
                } else if (position == selectionStart && selectionEnd > 0)
                {
                    MoveCursorCommand(*this,position, selectionStart, selectionEnd - 1).execute();
                }
            } else if ( selectionStart != selectionEnd ) {
                MoveCursorCommand(*this, selectionStart, selectionStart, selectionStart).execute();
            } else if (selectionStart > 0) {
                MoveCursorCommand(*this,selectionStart - 1, selectionStart - 1, selectionStart - 1).execute();
            }
            break;
        case (SDLK_RIGHT):
            if (shift) {
                if (position == selectionStart && selectionEnd < textBuffer.length()) {
                    MoveCursorCommand(*this,position, selectionStart, selectionEnd + 1).execute();
                }
                else if ( position == selectionEnd && selectionStart < textBuffer.length()) {
                    MoveCursorCommand(*this,position, selectionStart + 1, selectionEnd).execute();
                }
            }
            else if ( selectionStart != selectionEnd ) {
                MoveCursorCommand(*this, selectionEnd, selectionEnd, selectionEnd).execute();
            } else if ( selectionEnd < textBuffer.length()){
                MoveCursorCommand(*this, selectionEnd + 1, selectionEnd + 1, selectionEnd + 1).execute();
            }
            break;
        default: ;
        }
    }
}

void TextEditor::keyPressed(const bool ctrl, const bool alt, const bool shift, const char key)
{
    unsigned char unsignedKey = static_cast<unsigned char>(key);

    if ((std::isalpha(unsignedKey) && key >= 'a' && key <= 'z') || 
        (std::isalpha(unsignedKey) && key >= 'A' && key <= 'Z') || 
        std::ispunct(unsignedKey) || 
        key == ' ') {
        EnterCharCommand(*this, selectionStart, selectionEnd, key).execute();
    }
    else {
        EnterCharCommand(*this, selectionStart, selectionEnd, '#').execute();
    }
}

TextEditor::~TextEditor() = default;
