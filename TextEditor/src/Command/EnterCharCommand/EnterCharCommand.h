#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class EnterCharCommand final : public Command
{
    TextEditor& textEditor;
    int start, end;
    char character;

public :
    explicit EnterCharCommand(TextEditor& textEditor, int start, int end, char character);
    void execute() override;

    ~EnterCharCommand() override;
};
