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
    if (end <= textEditor.getTextBuffer().length() && start <= end)
    {
        std::string textBuffer = textEditor.getTextBuffer();
        if (start == end) {
            textBuffer.insert(start, 1, character);
            textEditor.setSelectionStart(start+1);
            textEditor.setSelectionEnd(end+1);
        } else {
            textBuffer.replace(start, end - start, 1, character);
            textEditor.setSelectionStart(start+1);
            textEditor.setSelectionEnd(start+1);
        }
        textEditor.setTextBuffer(textBuffer);
    }
}
