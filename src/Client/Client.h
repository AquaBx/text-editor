//
// Created by tomch on 14/10/2024.
//
#pragma once

#include "../Renderer/Renderer.h"
#include "../TextEditor/TextEditor.h"

class Client
{
    TextEditor textEditor;
    Renderer renderer;
    bool quit = false;
    void pollEvent();

public:
    Client(int width, int height);
    void run();
};
