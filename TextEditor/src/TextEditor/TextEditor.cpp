#include "TextEditor.h"

TextEditor::TextEditor() {}

void TextEditor::draw(Renderer& renderer)
{
    renderer.drawText(textBuffer);
}

void TextEditor::setCommand(Command *cmd) {
    this->command = cmd;
}

void TextEditor::executeCommand() {

}

void TextEditor::keyPressed(bool ctrl, bool alt, bool shift, const SDL_KeyCode key) {
    if( key )
    {
        textBuffer += static_cast<char>(key);
    }
/*

    if (key == SDLK_BACKSPACE || key == SDLK_DELETE) {
        DeleteTextCommand.execute(selectionStart, selectionEnd, this);
        return;
    }

    switch (ctrl) {
        case true:
            switch (key) {
                case SDLK_c:
                    CopyCommand.execute(selectionStart, selectionEnd, this);
                    return;
                case SDLK_v:
                    PasteCommand.execute(selectionStart, selectionEnd, this);
                    return;
                case SDLK_x:
                    CutCommand.execute(selectionStart, selectionEnd, this);
                    return;
                case SDLK_a:
                    MoveCursorCommand.execute(0, textBuffer.length - 1 , this);
                    return;
                default:
                    return;
            }
        case false:
            switch (alt) {
                case true:
                    switch (key) {
                        case (SDLK_UP):
                            MoveCursorCommand.execute(selectionStart, selectionEnd - line_length, this);
                            return;
                        case (SDLK_DOWN):
                            MoveCursorCommand.execute(selectionStart, selectionEnd + line_length, this);
                            return;
                        case (SDLK_LEFT):
                            MoveCursorCommand.execute(selectionStart, selectionEnd - 1, this);
                            return;
                        case (SDLK_RIGHT):
                            MoveCursorCommand.execute(selectionStart, selectionEnd + 1, this);
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
                            return;
                        default:
                            EnterCharCommand.execute(selectionStart, selectionEnd, this);
                            return;
                        default :
                            return;
                    }
            }
    }
    */
}

void TextEditor::undoCommand() {
    // pour V2 ça non ???
}

TextEditor::~TextEditor() {}
