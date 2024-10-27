#include "MoveCursorCommand.h"

MoveCursorCommand::~MoveCursorCommand() = default;

MoveCursorCommand::MoveCursorCommand(TextEditor& textEditor, const std::size_t position, const std::size_t start,
                                     const std::size_t end)
    : Command(textEditor),
      start(start),
      position(position),
      end(end)
{
}

void MoveCursorCommand::execute()
{
    if (end <= textEditor.getTextBuffer().length() && position <= textEditor.
                                                                  getTextBuffer().length())
    {
        textEditor.setSelectionStart(start);
        textEditor.setSelectionEnd(end);
        textEditor.setPosition(position);
    }
}
