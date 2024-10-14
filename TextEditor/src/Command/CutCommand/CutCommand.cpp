#include "CutCommand.h"
#include <string>

CutCommand::~CutCommand() = default;

CutCommand::CutCommand(TextEditor& textEditor, const int start, const int end): textEditor(textEditor), start(start), end(end){}

void CutCommand::execute() {
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && start <= end) {
        const std::string selectedText = textEditor.getTextBuffer().substr(start, end - start);
        textEditor.setClipboard(selectedText);
        textEditor.setTextBuffer(textEditor.getTextBuffer().erase(start, end - start));
    }
}
