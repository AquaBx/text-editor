//
// Created by tomch on 14/10/2024.
//

#include "Client.h"

Client::Client(const int width, const int height) : textEditor(TextEditor()), renderer(Renderer(width, height))
{
}

void Client::pollEvent()
{
    SDL_Event event;

    const Uint8* stateh = SDL_GetKeyboardState(nullptr);
    const bool ctrl = stateh[SDL_SCANCODE_LCTRL] || stateh[SDL_SCANCODE_RCTRL];
    const bool alt = stateh[SDL_SCANCODE_LALT] || stateh[SDL_SCANCODE_RALT];
    const bool shift = stateh[SDL_SCANCODE_LSHIFT] || stateh[SDL_SCANCODE_RSHIFT];

    while (SDL_PollEvent(&event) == 1)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                renderer.resize(event.window.data1, event.window.data2);
            }
        }
        else if (event.type == SDL_TEXTINPUT)
        {
            textEditor.keyPressed(ctrl, alt, shift, event.text.text[0]);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            textEditor.keyPressed(ctrl, alt, shift, static_cast<SDL_KeyCode>(event.key.keysym.sym));
        }
    }
}

void Client::run()
{
    while (!quit)
    {
        pollEvent();

        renderer.clear();
        textEditor.draw(renderer);
        renderer.render();
    }
}
