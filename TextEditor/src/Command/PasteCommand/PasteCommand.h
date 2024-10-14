#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class PasteCommand final : public Command
{
    TextEditor& textEditor;
    int start, end;

public :
    explicit PasteCommand(TextEditor& textEditor, int start, int end);


    ~PasteCommand() override;
    void execute() override;
};
