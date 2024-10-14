#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class CutCommand final : public Command {
    TextEditor& textEditor;
    int start,end;
    public :
        explicit CutCommand(TextEditor &textEditor, int start, int end);
        ~CutCommand() override;
        void execute() override;
};