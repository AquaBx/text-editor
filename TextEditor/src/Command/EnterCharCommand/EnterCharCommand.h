#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class EnterCharCommand final : public Command
{
    std::size_t start, end;
    char character;

public :
    explicit EnterCharCommand(TextEditor& textEditor, std::size_t start, std::size_t end, char character);
    void execute() override;

    ~EnterCharCommand() override;
};
