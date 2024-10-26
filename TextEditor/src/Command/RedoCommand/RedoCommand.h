#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class RedoCommand final : public Command
{
    public :
        explicit RedoCommand(TextEditor& textEditor);
        ~RedoCommand() override;
        void execute() override;
};
