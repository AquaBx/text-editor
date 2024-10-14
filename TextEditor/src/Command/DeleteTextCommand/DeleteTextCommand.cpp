#include "DeleteTextCommand.h"
#include <string>

DeleteTextCommand::~DeleteTextCommand() = default;

DeleteTextCommand::DeleteTextCommand(TextEditor &textEditor, int start, int end, char character) : textEditor(textEditor),start(start),end(end){}

void DeleteTextCommand::execute() {
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && start <= end) {
        textEditor.setTextBuffer(textEditor.getTextBuffer().erase(start, end - start));
    }
}
