#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class PasteCommand final : public Command
{
    TextEditor& textEditor;
    unsigned long long start, end;

public :
    explicit PasteCommand(TextEditor& textEditor, unsigned long long start, unsigned long long end);
    ~PasteCommand() override;
    void execute() override;
};
