#include "MoveCursorCommand.h"

MoveCursorCommand::~MoveCursorCommand() = default;

MoveCursorCommand::MoveCursorCommand(TextEditor& textEditor, const unsigned long long start, const unsigned long long end)
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
