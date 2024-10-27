#include "DeleteTextCommand.h"
#include <string>

DeleteTextCommand::~DeleteTextCommand() = default;

DeleteTextCommand::DeleteTextCommand(TextEditor& textEditor, const std::size_t start,
                                     const std::size_t end) : Command(textEditor), start(start), end(end)
{
}

void DeleteTextCommand::execute()
{
    if (end <= textEditor.getTextBuffer().length() && start <= end)
    {
        textEditor.setTextBuffer(textEditor.getTextBuffer().erase(start, end - start));
        textEditor.setSelectionStart(start);
        textEditor.setSelectionEnd(start);
        textEditor.setPosition(start);
    }
}
