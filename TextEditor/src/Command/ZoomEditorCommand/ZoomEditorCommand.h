#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class ZoomEditorCommand final : public Command
{
    float zoom;

public :
    explicit ZoomEditorCommand(TextEditor& textEditor, float zoom);
    void execute() override;
};
