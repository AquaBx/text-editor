#include "CopyCommand.h"
#include <string>

CopyCommand::~CopyCommand() = default;

CopyCommand::CopyCommand(TextEditor& textEditor, const unsigned long long start,
                         const unsigned long long end): textEditor(textEditor), start(start), end(end)
{
}

void CopyCommand::execute()
{
    if (end <= textEditor.getTextBuffer().length() && start <= end) {
        const std::string selectedText = textEditor.getTextBuffer().substr(start, end - start);
        textEditor.setClipboard(selectedText);
    }
}
