#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class EnterCharCommand final : public Command
{
    TextEditor& textEditor;
    unsigned long long start, end;
    char character;

public :
    explicit EnterCharCommand(TextEditor& textEditor, unsigned long long start, unsigned long long end, char character);
    void execute() override;

    ~EnterCharCommand() override;
};
