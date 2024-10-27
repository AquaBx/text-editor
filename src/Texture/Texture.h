//
// Created by tomch on 14/10/2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL_rect.h>
#include <SDL_render.h>

#include "../Renderer/Renderer.h"


class Texture
{
    SDL_Texture* texture;
    SDL_Rect rect{};
    SDL_Surface* surface;

public:
    Texture(const std::string& text, TTF_Font* font, SDL_Renderer* renderer, int x, int y);

    void draw(SDL_Renderer* renderer) const;

    ~Texture();
};
#endif //TEXTURE_H
