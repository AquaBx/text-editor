#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class CopyCommand final : public Command {
    TextEditor& textEditor;
    unsigned long long start, end;

public :
    explicit CopyCommand(TextEditor& textEditor, unsigned long long start, unsigned long long end);
    ~CopyCommand() override;
        void execute() override;
};
