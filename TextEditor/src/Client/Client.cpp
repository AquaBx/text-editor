//
// Created by tomch on 14/10/2024.
//

#include "Client.h"

Client::Client(int width,int height) : renderer(Renderer(width,height)), textEditor(TextEditor()) {}

void Client::pollEvent(){
    SDL_Event event;

    while (SDL_PollEvent(&event) == 1) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
}

void Client::run(){
    while (!quit){
        pollEvent();
        renderer.clear();
        textEditor.draw(renderer);
        renderer.render();
    }
}