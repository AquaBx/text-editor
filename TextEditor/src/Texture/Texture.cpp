//
// Created by tomch on 14/10/2024.
//

#include "Texture.h"

Texture::Texture(const std::string& text, TTF_Font* font, SDL_Renderer* renderer, int x, int y)
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

void Texture::draw(SDL_Renderer* renderer) const
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
};

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
};