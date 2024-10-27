//
// Created by tomch on 14/10/2024.
//
#pragma once
#include "../TextEditor/TextEditor.h"

class Command
{
protected:
    TextEditor& textEditor;

public :
    explicit Command(TextEditor& textEditor) : textEditor(textEditor)
    {
    }

    virtual ~Command() = default;
    virtual void execute() = 0;
};
