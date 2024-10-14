#include "MoveCursorCommand.h"

MoveCursorCommand::~MoveCursorCommand() {}

void MoveCursorCommand::execute(int start, int end, TextEditor& textEditor) {
    textEditor.setSelectionStart(start);
    textEditor.setSelectionEnd(end);
}
