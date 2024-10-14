#include "EnterCharCommand.h"
#include <string>

EnterCharCommand::~EnterCharCommand() {}

void EnterCharCommand::execute(int start, int end, char character, TextEditor& editor) {
    if (start >= 0 && end <= editor.getTextBuffer().length() && start <= end) {
        std::string textBuffer = editor.getTextBuffer();        
        if (start == end) {
            textBuffer.insert(start, 1, character);
        } else {
            textBuffer.replace(start, end - start, 1, character);
        }
        editor.setTextBuffer(textBuffer);
    }
}
