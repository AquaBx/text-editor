#include "CopyCommand.h"
#include <string>

CopyCommand::~CopyCommand() = default;

CopyCommand::CopyCommand(TextEditor& textEditor, const int start, const int end):textEditor(textEditor), start(start), end(end){}

void CopyCommand::execute() {
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && start <= end) {
        const std::string selectedText = textEditor.getTextBuffer().substr(start, end - start);
        textEditor.setClipboard(selectedText);
    }
}
