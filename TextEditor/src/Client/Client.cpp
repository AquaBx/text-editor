//
// Created by tomch on 14/10/2024.
//

#include "Client.h"

#include "../Texture/Texture.h"

Client::Client(const int width, const int height) : textEditor(TextEditor()), renderer(Renderer(width, height))
{
}

void Client::pollEvent(){
    SDL_Event event;

    SDL_Keycode latest = SDLK_UNKNOWN;

    while (SDL_PollEvent(&event) == 1) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                renderer.resize(event.window.data1, event.window.data2);
            }
        }

        SDL_Keycode key = event.key.keysym.sym;
        const bool isDown = event.type == SDL_KEYDOWN;

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

    if (latest != SDLK_UNKNOWN)
    {
        textEditor.keyPressed(ctrl,alt,shift,static_cast<SDL_KeyCode>(latest));
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