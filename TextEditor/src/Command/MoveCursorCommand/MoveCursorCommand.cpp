#include "MoveCursorCommand.h"

MoveCursorCommand::~MoveCursorCommand() {}
MoveCursorCommand::MoveCursorCommand(TextEditor& textEditor, const int start, const int end)
    : textEditor(textEditor),
      start(start),
      end(end)
{
}

void MoveCursorCommand::execute()
{
    textEditor.setSelectionStart(start);
    textEditor.setSelectionEnd(end);
}
