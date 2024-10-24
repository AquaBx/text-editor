#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class DeleteTextCommand final : public Command {
    TextEditor& textEditor;
    unsigned long long start, end;

public :
    explicit DeleteTextCommand(TextEditor& textEditor, unsigned long long start, unsigned long long end);
    ~DeleteTextCommand() override;
    void execute() override;
};
