#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class MoveCursorCommand final : public Command
{
    TextEditor& textEditor;
    int start, end;

public :
    explicit MoveCursorCommand(TextEditor& textEditor, int start, int end);

    void execute() override;

    ~MoveCursorCommand() override;
};
