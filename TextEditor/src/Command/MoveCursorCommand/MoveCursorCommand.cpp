#include "MoveCursorCommand.h"

MoveCursorCommand::~MoveCursorCommand() = default;

MoveCursorCommand::MoveCursorCommand(TextEditor& textEditor, const std::size_t position, const std::size_t start, const std::size_t end)
    : textEditor(textEditor),
      start(start),
      end(end),
    position(position)
{
}

void MoveCursorCommand::execute()
{
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && position >= 0 && position <= textEditor.getTextBuffer().length()){
        textEditor.setSelectionStart(start);
        textEditor.setSelectionEnd(end);
        textEditor.setPosition(position);
    }

}
