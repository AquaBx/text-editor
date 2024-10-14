//
// Created by tomch on 14/10/2024.
//

#include "Renderer.h"


Renderer::Renderer(const int width, const int height) : width(width), height(height)
{
    const char* fontPath = "resources/OpenSans.ttf";

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    TTF_Init();

    font = TTF_OpenFont(fontPath, 24);

    if (font == nullptr)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
}

void Renderer::clear() const
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void Renderer::resize(const int width, const int height) const
{
    SDL_SetWindowSize(window, width, height);
}

Renderer::~Renderer() {
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::drawText(const std::string& text) const
{
    if (!text.empty())
    {
        const Texture texture(text, font, renderer);
        texture.draw(renderer);
    }
}

void Renderer::render() const
{
    SDL_RenderPresent(renderer);
};

void Renderer::drawCursor(const std::string& text, unsigned long long start, unsigned long long end) const
{
    SDL_Rect r;
    r.x = (start - 1) * 12;
    r.y = 0;
    r.w = (end - start + 2) * 12;
    r.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);

    // Render rect
    SDL_RenderFillRect(renderer, &r);
}
