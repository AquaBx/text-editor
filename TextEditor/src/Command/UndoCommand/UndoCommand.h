#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class UndoCommand final : public Command
{
    public :
        explicit UndoCommand(TextEditor& textEditor);
        void execute() override;
};