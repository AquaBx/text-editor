#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class CopyCommand final : public Command {
    TextEditor& textEditor;
    int start,end;
    public :
        explicit CopyCommand(TextEditor &textEditor, int start, int end);
        ~CopyCommand() override;
        void execute() override;
};
