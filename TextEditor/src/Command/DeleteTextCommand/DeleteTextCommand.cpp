#include "DeleteTextCommand.h"
#include <string>

DeleteTextCommand::~DeleteTextCommand() = default;

DeleteTextCommand::DeleteTextCommand(TextEditor& textEditor, const unsigned long long start,
                                     const unsigned long long end) : textEditor(textEditor), start(start), end(end)
{
}

void DeleteTextCommand::execute()
{
    if (end <= textEditor.getTextBuffer().length() && start <= end) {
        textEditor.setTextBuffer(textEditor.getTextBuffer().erase(start, end - start));
    }
}
