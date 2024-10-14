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
    Texture(const std::string& text, TTF_Font* font, SDL_Renderer* renderer)
    {
        constexpr SDL_Color textColor = {255, 255, 255, 0};
        surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        rect = {
            0,
            0,
            surface->w,
            surface->h
        };
    };

    void draw(SDL_Renderer* renderer) const
    {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    };

    ~Texture()
    {
        SDL_DestroyTexture(texture);
    };
};


#endif //TEXTURE_H
