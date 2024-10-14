#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class CutCommand final : public Command {
    TextEditor& textEditor;
    unsigned long long start, end;

public :
    explicit CutCommand(TextEditor& textEditor, unsigned long long start, unsigned long long end);
    ~CutCommand() override;
        void execute() override;
};