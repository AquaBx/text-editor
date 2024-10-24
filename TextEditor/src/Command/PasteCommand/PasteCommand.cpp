#include "PasteCommand.h"
#include <string>

PasteCommand::~PasteCommand() = default;

PasteCommand::PasteCommand(TextEditor& textEditor, const std::size_t start, const std::size_t end)
    : Command(textEditor),
      start(start),
      end(end)
{
}

void PasteCommand::execute()
{
    const std::string clipboardContent = textEditor.getClipboard();
    std::string textBuffer = textEditor.getTextBuffer();
    if (start == end)
    {
        textBuffer.insert(start, clipboardContent);
    }
    else
    {
        textBuffer.replace(start, end - start, clipboardContent);
    }
    textEditor.setTextBuffer(textBuffer);
    const std::size_t position = start + clipboardContent.length();
    textEditor.setSelectionStart(position);
    textEditor.setSelectionEnd(position);
    textEditor.setPosition(position);
}
