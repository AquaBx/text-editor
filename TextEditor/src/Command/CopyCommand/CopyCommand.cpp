#include "CopyCommand.h"
#include <string>

CopyCommand::~CopyCommand() {}

void CopyCommand::execute(int start, int end, TextEditor& textEditor) {
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && start <= end) {
        std::string selectedText = textEditor.getTextBuffer().substr(start, end - start);
        textEditor.setClipboard(selectedText);
    }
}
