#include "CopyCommand.h"
#include <string>

CopyCommand::~CopyCommand() = default;

CopyCommand::CopyCommand(TextEditor& textEditor, const std::size_t start,
                         const std::size_t end): Command(textEditor), start(start), end(end)
{
}

void CopyCommand::execute()
{
    if (end <= textEditor.getTextBuffer().length() && start <= end)
    {
        const std::string selectedText = textEditor.getTextBuffer().substr(start, end - start);
        textEditor.setClipboard(selectedText);
    }
}
