#include "DeleteTextCommand.h"
#include <string>

DeleteTextCommand::~DeleteTextCommand() {}

void DeleteTextCommand::execute(int start, int end, TextEditor& textEditor) {
    if (start >= 0 && end <= textEditor.getTextBuffer().length() && start <= end) {
        textEditor.setTextBuffer(textEditor.getTextBuffer().erase(start, end - start));
    }
}
