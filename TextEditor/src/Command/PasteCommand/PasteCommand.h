#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class PasteCommand final : public Command
{
    TextEditor& textEditor;
    std::size_t start, end;

public :
    explicit PasteCommand(TextEditor& textEditor, std::size_t start, std::size_t end);
    ~PasteCommand() override;
    void execute() override;
};
