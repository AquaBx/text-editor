#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class MoveCursorCommand final : public Command
{
    TextEditor& textEditor;
    unsigned long long start, end;

public :
    explicit MoveCursorCommand(TextEditor& textEditor, unsigned long long start, unsigned long long end);

    void execute() override;

    ~MoveCursorCommand() override;
};
