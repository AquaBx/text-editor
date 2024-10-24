#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class ZoomEditorCommand final : public Command
{
    TextEditor& textEditor;
    float zoom;

public :
    explicit ZoomEditorCommand(TextEditor& textEditor, float zoom);
    ~ZoomEditorCommand() override;
    void execute() override;
};
