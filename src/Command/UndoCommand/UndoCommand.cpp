//
// Created by tomch on 26/10/2024.
//

#include "UndoCommand.h"

UndoCommand::UndoCommand(TextEditor& textEditor)
    : Command(textEditor)
{
}

void UndoCommand::execute()
{
    textEditor.undoCommand();
}
