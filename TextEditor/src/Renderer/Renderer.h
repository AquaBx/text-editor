//
// Created by tomch on 14/10/2024.
//

#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Renderer {
private:
    SDL_Texture * texture;
    SDL_Rect * rect;

    SDL_Renderer * renderer;
    SDL_Window *window;

    int width;
    int height;
    TTF_Font *font;
    void resize();
public:

    void drawText(std::string text);

    void render();
    Renderer(int width, int height);
    void clear();
    ~Renderer();
};