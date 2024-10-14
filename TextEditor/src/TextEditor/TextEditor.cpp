#include "TextEditor.h"

TextEditor::TextEditor() {}

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

int TextEditor::getSelectionStart() {
    return selectionStart;
}

void TextEditor::setSelectionStart(int start) {
    selectionStart = start;
}

int TextEditor::getSelectionEnd() {
    return selectionEnd;
}

void TextEditor::setSelectionEnd(int end) {
    selectionEnd = end;
}

void TextEditor::draw(Renderer& renderer) {
    renderer.drawText(textBuffer);
}

void TextEditor::setCommand(Command *cmd) {
    this->command = cmd;
}

void TextEditor::executeCommand() {

}

void TextEditor::keyPressed(bool ctrl, bool alt, bool shift, const SDL_KeyCode key) {
    /*
    if (key) {
        textBuffer += static_cast<char>(key);
    }

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
                    MoveCursorCommand.execute(0, textBuffer.length() - 1 , this);
                    return;
                default:
                    return;
            }
        case false:
            switch (alt) {
                case true:
                    switch (key) {
                        case (SDLK_UP):
                            MoveCursorCommand.execute(selectionStart, selectionEnd - lineLength, this);
                            return;
                        case (SDLK_DOWN):
                            MoveCursorCommand.execute(selectionStart, selectionEnd + lineLength, this);
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
                    }
            }
    }
    */
}

void TextEditor::undoCommand() {
    // pour V2 ça non ???
}

TextEditor::~TextEditor() {}
