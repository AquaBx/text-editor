//
// Created by tomch on 14/10/2024.
//
#pragma once


// c'est une interface
class Command {
public : 
    virtual void execute() = 0;
    virtual void undo() = 0;

    virtual ~Command() = 0;
};