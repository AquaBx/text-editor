#include "PasteCommand.h"
#include <string>

PasteCommand::~PasteCommand() {}

void PasteCommand::execute(int start, int end, TextEditor& textEditor) {
    std::string clipboardContent = textEditor.getClipboard();
    std::string textBuffer = textEditor.getTextBuffer();
    if (start == end) {
        textBuffer.insert(start, clipboardContent);
    } else {
        textBuffer.replace(start, end - start, clipboardContent);
    }
    textEditor.setTextBuffer(textBuffer);
    int position = start + clipboardContent.length();
    textEditor.setSelectionStart(position);
    textEditor.setSelectionEnd(position);
}
