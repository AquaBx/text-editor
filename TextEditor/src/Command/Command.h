//
// Created by tomch on 14/10/2024.
//
#pragma once
#include "../Snapshot/Snapshot.h"
#include "../TextEditor/TextEditor.h"

class Command {
    protected:
        TextEditor& textEditor;
        Snapshot * snapshot = nullptr;

    public :
        explicit Command(TextEditor& textEditor) : textEditor(textEditor)
        {
            snapshot = new Snapshot( textEditor.textBuffer, textEditor.position, textEditor.selectionStart, textEditor.selectionEnd );
        };

        virtual ~Command() {
            delete snapshot;
        };

        virtual void execute() = 0;

        virtual void undo()
        {
            textEditor.restoreSnapshot(snapshot);
        };
};
