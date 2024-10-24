#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class CopyCommand final : public Command
{
    std::size_t start, end;

public :
    explicit CopyCommand(TextEditor& textEditor, std::size_t start, std::size_t end);
    ~CopyCommand() override;
    void execute() override;
};
