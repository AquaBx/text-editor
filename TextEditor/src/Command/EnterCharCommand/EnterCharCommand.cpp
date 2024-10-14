#include "EnterCharCommand.h"
#include <string>

EnterCharCommand::~EnterCharCommand() = default;


EnterCharCommand::EnterCharCommand(TextEditor& textEditor, const unsigned long long start, const unsigned long long end,
                                   const char character)
    : textEditor(textEditor),
      start(start),
      end(end),
      character(character)
{
}

void EnterCharCommand::execute()
{
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && start <= end)
    {
        std::string textBuffer = textEditor.getTextBuffer();
        if (start == end) {
            textBuffer.insert(start, 1, character);
        } else {
            textBuffer.replace(start, end - start, 1, character);
        }
        textEditor.setTextBuffer(textBuffer);
    }
}
