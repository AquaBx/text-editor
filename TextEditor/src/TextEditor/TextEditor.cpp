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
#include "../Command/UndoCommand/UndoCommand.h"
#include "../Command/RedoCommand/RedoCommand.h"

TextEditor::TextEditor() = default;

std::string TextEditor::getTextBuffer() const
{
    return textBuffer;
}

void TextEditor::setTextBuffer(std::string t)
{
    textBuffer = t;
}

std::string TextEditor::getClipboard() const
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
    if (ctrl && key==SDLK_m)
    {
        macroRecord=!macroRecord;
        if (macroRecord)
        {
            macroHistory = {};
        }
    }
    else if (macroRecord) {
        if (!alt || key!=SDLK_m)
        {
            macroHistory.push_back({ctrl,alt,shift,CombinaisonType::KEYCODE, static_cast<SDL_Keycode>(key)});
        }
    }
    else if ((key == SDLK_BACKSPACE || key == SDLK_DELETE) && selectionStart != selectionEnd)
    {
        executeCommand(new DeleteTextCommand(*this, selectionStart, selectionEnd));
    }
    else if (key == SDLK_BACKSPACE)
    {
        executeCommand(new DeleteTextCommand(*this, selectionStart - 1, selectionStart));
    }
    else if (key == SDLK_DELETE)
    {
        executeCommand(new DeleteTextCommand(*this, selectionStart, selectionStart + 1));
    }
    else if (key == SDLK_RETURN || key ==  SDLK_KP_ENTER)
    {
        executeCommand(new EnterCharCommand(*this, selectionStart, selectionEnd, '\n'));
    }
    else if (ctrl)
    {
        switch (key)
        {
        case SDLK_c:
            CopyCommand(*this, selectionStart, selectionEnd).execute();
            break;
        case SDLK_z:
            UndoCommand(*this).execute();
            break;
        case SDLK_y:
            RedoCommand(*this).execute();
            break;
        case SDLK_v:
            executeCommand(new PasteCommand(*this, selectionStart, selectionEnd));
            break;
        case SDLK_x:
            executeCommand(new CutCommand(*this, selectionStart, selectionEnd));
            break;
        case SDLK_a:
            MoveCursorCommand(*this, 0, 0, textBuffer.length()).execute();
            break;
        case SDLK_KP_MINUS:
            ZoomEditorCommand(*this, -0.25).execute();
            break;
        case SDLK_KP_PLUS:
            ZoomEditorCommand(*this, 0.25).execute();
            break;
        default: ;
        }
    }
    else if (alt)
    {
        switch (key)
        {
        case SDLK_m:
                for (const Combinaison c:macroHistory)
                {
                    if (c.type == CombinaisonType::KEYCODE)
                    {
                        keyPressed(c.ctrl,c.alt,c.shift,static_cast<SDL_KeyCode>(c.keyCode));
                    }
                    else
                    {
                        keyPressed(c.ctrl,c.alt,c.shift,c.charCode);
                    }
                };
            default:
                break;
        }
    }
    else
    {
        switch (key)
        {
        case (SDLK_UP):
            MoveCursorCommand(*this, 0, 0, 0).execute();
            break;
        case (SDLK_DOWN):
            MoveCursorCommand(*this, textBuffer.length(), textBuffer.length(), textBuffer.length()).execute();
            break;
        case (SDLK_LEFT):
            if (shift)
            {
                if (position == selectionEnd && selectionStart > 0)
                {
                    MoveCursorCommand(*this, position, selectionStart - 1, selectionEnd).execute();
                }
                else if (position == selectionStart && selectionEnd > 0)
                {
                    MoveCursorCommand(*this, position, selectionStart, selectionEnd - 1).execute();
                }
            }
            else if (selectionStart != selectionEnd)
            {
                MoveCursorCommand(*this, selectionStart, selectionStart, selectionStart).execute();
            }
            else if (selectionStart > 0)
            {
                MoveCursorCommand(*this, selectionStart - 1, selectionStart - 1, selectionStart - 1).execute();
            }
            break;
        case (SDLK_RIGHT):
            if (shift)
            {
                if (position == selectionStart && selectionEnd < textBuffer.length())
                {
                    MoveCursorCommand(*this, position, selectionStart, selectionEnd + 1).execute();
                }
                else if (position == selectionEnd && selectionStart < textBuffer.length())
                {
                    MoveCursorCommand(*this, position, selectionStart + 1, selectionEnd).execute();
                }
            }
            else if (selectionStart != selectionEnd)
            {
                MoveCursorCommand(*this, selectionEnd, selectionEnd, selectionEnd).execute();
            }
            else if (selectionEnd < textBuffer.length())
            {
                MoveCursorCommand(*this, selectionEnd + 1, selectionEnd + 1, selectionEnd + 1).execute();
            }
            break;
        default: ;
        }
    }
}

void TextEditor::keyPressed(const bool ctrl, const bool alt, const bool shift, const char key)
{
    if (macroRecord)
    {
        macroHistory.push_back({ctrl,alt,shift,CombinaisonType::CHARCODE, key});
    }
    else if (
        (std::isalpha(key) && ((key >= 'a' && key <= 'z') || key >= 'A' && key <= 'Z'))
        || std::ispunct(key) || key == ' '
    )
    {
        executeCommand(new EnterCharCommand(*this, selectionStart, selectionEnd, key));
    }
    else
    {
        executeCommand(new EnterCharCommand(*this, selectionStart, selectionEnd, '#'));
    }
}

TextEditor::~TextEditor()
{
    while (!snapshotHistory.empty())
    {
        delete snapshotHistory.top();
        snapshotHistory.pop();
    }
    while (!snapshotRedoHistory.empty())
    {
        delete snapshotRedoHistory.top();
        snapshotRedoHistory.pop();
    }
};

void TextEditor::restoreSnapshot(const Snapshot* snapshot)
{
    position = snapshot->position;
    textBuffer = snapshot->textBuffer;
    selectionStart = snapshot->selectionStart;
    selectionEnd = snapshot->selectionEnd;
}

void TextEditor::executeCommand(Command* command)
{
    Snapshot* snapshot = new Snapshot(textBuffer, position, selectionStart, selectionEnd);
    snapshotHistory.push(snapshot);
    command->execute();

    while (!snapshotRedoHistory.empty())
    {
        delete snapshotRedoHistory.top();
        snapshotRedoHistory.pop();
    }
}

void TextEditor::undoCommand()
{
    Snapshot* snapshot2 = new Snapshot(textBuffer, position, selectionStart, selectionEnd);
    if (!snapshotHistory.empty())
    {
        const Snapshot* snapshot = snapshotHistory.top();
        snapshotHistory.pop();
        snapshotRedoHistory.push(snapshot2);
        restoreSnapshot(snapshot);
    }
}

void TextEditor::redoCommand()
{
    Snapshot* snapshot2 = new Snapshot(textBuffer, position, selectionStart, selectionEnd);
    if (!snapshotRedoHistory.empty())
    {
        const Snapshot* snapshot = snapshotRedoHistory.top();
        snapshotRedoHistory.pop();
        snapshotHistory.push(snapshot2);
        restoreSnapshot(snapshot);
    }
}
