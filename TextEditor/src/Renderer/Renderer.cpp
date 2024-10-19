//
// Created by tomch on 14/10/2024.
//

#include "Renderer.h"
#include "../Debug/Debug.h"


Renderer::Renderer(const int width, const int height) : width(width), height(height)
{
    const char* fontPath = "resources/OpenSans.ttf";

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

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

void Renderer::resize(const int width, const int height)
{
    SDL_SetWindowSize(window, width, height);
    this->width = width;
    this->height = height;
}

Renderer::~Renderer()
{
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::drawText(std::string text, size_t cursorStart, size_t cursorEnd) const
{
    int x = 0;
    int y = 0;

    int space_size_x = 0;
    int space_size_y = 0;
    TTF_SizeText(font, " ", &space_size_x, &space_size_y);

    // ceci est juste pour décalé à droite la première ligne
    text = "\r" + text;
    cursorStart += 1;
    cursorEnd += 1;

    while (!text.empty())
    {
        std::size_t retour = text.find('\n');
        std::string ligne;
        if (retour != std::string::npos)
        {
            ligne = text.substr(0, retour);
            text = '\r' + text.erase(0, retour + 1);
        }
        else
        {
            ligne = text;
            text = "";
        }
        int w = 0;
        int h = space_size_y;

        while (!ligne.empty())
        {
            std::size_t space = ligne.find(' ');

            std::string word;
            if (space != std::string::npos)
            {
                word = ligne.substr(0, space + 1);
                ligne = ligne.erase(0, space + 1);
            }
            else
            {
                word = ligne;
                ligne = "";
            }

            TTF_SizeText(font, word.c_str(), &w, &h);
            if (w + x > width)
            {
                y += h;
                x = 0;
            }

            if (cursorStart <= 0 + word.length())
            {
                int ax = 0;
                int aw = 0;
                TTF_SizeText(font, word.substr(0, cursorStart).c_str(), &ax, nullptr);
                if (cursorEnd <= 0 + word.length())
                {
                    TTF_SizeText(font, word.substr(cursorStart, cursorEnd - cursorStart).c_str(), &aw, nullptr);
                }
                else
                {
                    TTF_SizeText(font, word.substr(cursorStart, word.length()).c_str(), &aw, nullptr);
                    cursorStart += word.length() - cursorStart;
                }
                drawCursor(x + ax, y, aw, h);
            }

            cursorStart -= word.length();
            cursorEnd -= word.length();

            Texture(word, font, renderer, x, y).draw(renderer);

            x += w;
        }
        x = 0;
        y += h;
    }
}


void Renderer::render() const
{
    SDL_RenderPresent(renderer);
};

void Renderer::drawCursor(int x, int y, int w, int h) const
{
    if (w == 0)
    {
        w = 4;
        x -= w / 2;
    }

    SDL_Rect r{x, y, w, h};

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);

    // Render rect
    SDL_RenderFillRect(renderer, &r);
}
