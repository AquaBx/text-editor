//
// Created by tomch on 14/10/2024.
//
#pragma once

#include "../Renderer/Renderer.h"
#include "../TextEditor/TextEditor.h"

class Client {
private:
    TextEditor textEditor;
    Renderer renderer;
    //SDL_Event event;
    bool quit = false;
    void pollEvent();


    bool ctrl = false;
    bool alt = false;
    bool shift = false;

public:
    Client(int width,int height);
    void run();
};