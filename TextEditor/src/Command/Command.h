//
// Created by tomch on 14/10/2024.
//
#pragma once

class Command {
public :
    virtual ~Command() = default;
    virtual void execute() = 0;
    //virtual void undo() = 0; // dans la v2 ça plutôt / pour moi non
};
