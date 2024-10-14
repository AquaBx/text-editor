//
// Created by tomch on 14/10/2024.
//

#include "Client.h"
#include "../Texture/Texture.h"

Client::Client(int width,int height) : renderer(Renderer(width,height)), textEditor(TextEditor()) {}

void Client::pollEvent(){
    SDL_Event event;

    SDL_Keycode latest = SDLK_UNKNOWN;

    while (SDL_PollEvent(&event) == 1) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }

        SDL_Keycode key = event.key.keysym.sym;
        bool isDown = event.type==SDL_KEYDOWN;

        switch (key) {
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                ctrl = isDown;
                break;

            case SDLK_LALT:
            case SDLK_RALT:
                alt = isDown;
                break;

            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                shift = isDown;
                break;

            default:
                latest = isDown ? key : latest;
                break;
        }

    }

    textEditor.keyPressed(ctrl,alt,shift,static_cast<SDL_KeyCode>(latest));
}

void Client::run(){
    while (!quit){
        pollEvent();
        renderer.clear();

        textEditor.draw(renderer);

        renderer.render();
    }
}