//
// Created by tomch on 14/10/2024.
//

#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../Texture/Texture.h"

class Renderer
{
    int width;
    int height;

    TTF_Font* font;
    SDL_Renderer* renderer{};
    SDL_Window* window{};

public:
    void drawText(std::string text, size_t cursorStart, size_t cursorEnd) const;
    void drawCursor(int x, int y, int w, int h) const;
    void render() const;
    Renderer(int width, int height);
    void clear() const;
    void resize(int width, int height);

    ~Renderer();
};
