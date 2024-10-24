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
    Texture(const std::string& text, TTF_Font* font, SDL_Renderer* renderer, int x, int y)
    {
        constexpr SDL_Color textColor = {8, 9, 10, 0};
        surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        rect = {
            x,
            y,
            surface->w,
            surface->h
        };
        SDL_FreeSurface(surface);
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
