#include "PasteCommand.h"
#include <string>

PasteCommand::~PasteCommand() = default;

PasteCommand::PasteCommand(TextEditor& textEditor, const int start, const int end)
    : textEditor(textEditor),
      start(start),
      end(end)
{
}

void PasteCommand::execute()
{
    std::string clipboardContent = textEditor.getClipboard();
    std::string textBuffer = textEditor.getTextBuffer();
    if (start == end) {
        textBuffer.insert(start, clipboardContent);
    } else {
        textBuffer.replace(start, end - start, clipboardContent);
    }
    textEditor.setTextBuffer(textBuffer);
    const int position = start + clipboardContent.length();
    textEditor.setSelectionStart(position);
    textEditor.setSelectionEnd(position);
}
