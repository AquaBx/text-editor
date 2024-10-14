#include "PasteCommand.h"
#include <string>

PasteCommand::~PasteCommand() = default;

PasteCommand::PasteCommand(TextEditor& textEditor, const unsigned long long start, const unsigned long long end)
    : textEditor(textEditor),
      start(start),
      end(end)
{
}

void PasteCommand::execute()
{
    const std::string clipboardContent = textEditor.getClipboard();
    std::string textBuffer = textEditor.getTextBuffer();
    if (start == end) {
        textBuffer.insert(start, clipboardContent);
    } else {
        textBuffer.replace(start, end - start, clipboardContent);
    }
    textEditor.setTextBuffer(textBuffer);
    const unsigned long long position = start + clipboardContent.length();
    textEditor.setSelectionStart(position);
    textEditor.setSelectionEnd(position);
}
