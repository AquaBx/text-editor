#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class MoveCursorCommand final : public Command
{
    TextEditor& textEditor;
    std::size_t start, position, end;

public :
    explicit MoveCursorCommand(TextEditor& textEditor, std::size_t position, std::size_t start, std::size_t end);

    void execute() override;

    ~MoveCursorCommand() override;
};
