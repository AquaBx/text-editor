#include "TextEditor.h"

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
        return;
    }
    else if (key == SDLK_BACKSPACE)
    {
        DeleteTextCommand(*this, selectionStart - 1, selectionStart).execute();
        return;
    }
    else if (key == SDLK_DELETE)
    {
        DeleteTextCommand(*this, selectionStart, selectionStart + 1).execute();
        return;
    }
    else if (key == SDLK_RETURN)
    {
        EnterCharCommand(*this, selectionStart, selectionEnd, '\n').execute();
        return;
    }

    switch (ctrl)
    {
    case true:
        switch (key)
        {
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
            MoveCursorCommand(*this, 0, textBuffer.length()).execute();
            return;
        default:
            return;
        }
    case false:
        switch (key)
        {
        case (SDLK_UP):
            MoveCursorCommand(*this, 0, 0).execute();
            return;
        case (SDLK_DOWN):
            MoveCursorCommand(*this, textBuffer.length(), textBuffer.length()).execute();
            return;
        case (SDLK_LEFT):
            MoveCursorCommand(*this, (selectionStart == 0 ? 0 : selectionStart - 1),
                              selectionEnd - (shift ? 0 : 1)).execute();
            return;
        case (SDLK_RIGHT):
            MoveCursorCommand(*this, selectionStart + (shift ? 0 : 1),
                              (selectionEnd == textBuffer.length() ? selectionEnd : selectionEnd + 1)).execute();
            return;
        case (SDLK_UNKNOWN):
            return;
        default:
            char character = static_cast<char>(key);

            if (alt)
            {
                switch (key)
                {
                case SDLK_2: character = '~'; break;
                case SDLK_3: character = '#'; break;
                case SDLK_4: character = '{'; break;
                case SDLK_5: character = '['; break;
                case SDLK_6: character = '|'; break;
                case SDLK_7: character = '`'; break;
                case SDLK_8: character = '\\'; break;
                case SDLK_9: character = '^'; break;
                case SDLK_0: character = '@'; break;
                case SDLK_LEFTBRACKET: character = ']'; break; // nothing appears
                case SDLK_RIGHTBRACKET: character = '}'; break; // nothing appears
                default:
                    return;
                }
            }
            else if (shift)
            {
                switch (key)
                {
                case SDLK_1: character = '1'; break;
                case SDLK_2: character = '2'; break;
                case SDLK_3: character = '3'; break;
                case SDLK_4: character = '4'; break;
                case SDLK_5: character = '5'; break;
                case SDLK_6: character = '6'; break;
                case SDLK_7: character = '7'; break;
                case SDLK_8: character = '8'; break;
                case SDLK_9: character = '9'; break;
                case SDLK_0: character = '0'; break;
                case SDLK_SEMICOLON: character = '.'; break;
                case SDLK_COMMA: character = '?'; break;
                // case SDLK_after : character = '°'; break; // for instance, ")"
                // case SDLK_stillafter : character = '+'; break; // for instance, "+"
                default:
                    if (character >= 'a' && character <= 'z')
                    {
                        character = static_cast<char>(key - ('a' - 'A'));
                    }
                    break;
                }
            }
            else
            {
                switch (key)
                {
                case SDLK_1: character = '&'; break;
                case SDLK_2: character = 'é'; break; // does not work (c symbol for brands instead)
                case SDLK_3: character = '"'; break;
                case SDLK_4: character = '\''; break;
                case SDLK_5: character = '('; break;
                case SDLK_6: character = '-'; break;
                case SDLK_7: character = 'è'; break; // does not work (¨ instead)
                case SDLK_8: character = '_'; break;
                case SDLK_9: character = 'ç'; break; // does not work (§ instead)
                case SDLK_0: character = 'à'; break; // does not work (space instead)
                default:
                    break;
                }
            }

            EnterCharCommand(*this, selectionStart, selectionEnd, character).execute();
            return;
        }
    }
}

void TextEditor::undoCommand()
{
    // pour V2 ça non ???
}

TextEditor::~TextEditor() = default;
