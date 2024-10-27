#include "CutCommand.h"
#include <string>

CutCommand::~CutCommand() = default;

CutCommand::CutCommand(TextEditor& textEditor, const std::size_t start,
                       const std::size_t end): Command(textEditor), start(start), end(end)
{
}

void CutCommand::execute()
{
    if (end <= textEditor.getTextBuffer().length() && start <= end)
    {
        const std::string selectedText = textEditor.getTextBuffer().substr(start, end - start);
        textEditor.setClipboard(selectedText);
        textEditor.setTextBuffer(textEditor.getTextBuffer().erase(start, end - start));
        textEditor.setSelectionEnd(textEditor.getSelectionStart());
        textEditor.setPosition(textEditor.getSelectionStart());
    }
}
