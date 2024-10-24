#pragma once

#include "../Command.h"
#include "../../TextEditor/TextEditor.h"

class DeleteTextCommand final : public Command {
    TextEditor& textEditor;
    std::size_t start, end;

public :
    explicit DeleteTextCommand(TextEditor& textEditor, std::size_t start, std::size_t end);
    ~DeleteTextCommand() override;
    void execute() override;
};
