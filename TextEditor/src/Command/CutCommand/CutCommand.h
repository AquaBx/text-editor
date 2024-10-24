#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class CutCommand final : public Command
{
    TextEditor& textEditor;
    std::size_t start, end;

public :
    explicit CutCommand(TextEditor& textEditor, std::size_t start, std::size_t end);
    ~CutCommand() override;
    void execute() override;
};
