//
// Created by tomch on 26/10/2024.
//

#include "RedoCommand.h"

RedoCommand::RedoCommand(TextEditor& textEditor)
    : Command(textEditor)
{
}

void RedoCommand::execute()
{
    textEditor.redoCommand();
}
