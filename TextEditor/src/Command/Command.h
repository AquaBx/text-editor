//
// Created by tomch on 14/10/2024.
//
#pragma once
#include "TextEditor/TextEditor.h"

class Command {
public : 
    virtual void execute(int start, int end, TextEditor& textEditor) = 0;
    virtual void execute(int start, int end, char character, TextEditor& textEditor) = 0;

    virtual void undo() = 0; // dans la v2 ça plutôt

    virtual ~Command() = 0;
};
