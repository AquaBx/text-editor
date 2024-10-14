#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class DeleteTextCommand final : public Command {
    TextEditor& textEditor;
    int start,end;
    public :
        explicit DeleteTextCommand(TextEditor &textEditor, int start, int end);
        ~DeleteTextCommand() override;
        void execute() override;
};
