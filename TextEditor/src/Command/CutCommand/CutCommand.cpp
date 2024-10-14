#include "CutCommand.h"
#include <string>

CutCommand::~CutCommand() {}

void CutCommand::execute(int start, int end, TextEditor& textEditor) {
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && start <= end) {
        std::string selectedText = textEditor.getTextBuffer().substr(start, end - start);
        textEditor.setClipboard(selectedText);
        textEditor.setTextBuffer(textEditor.getTextBuffer().erase(start, end - start));
    }
}
