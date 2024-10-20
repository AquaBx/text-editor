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
            
            while (w + x > width)
            {
                std::size_t cutIndex = word.length();
                int currentWidth = 0;

                for (std::size_t i = 0; i < word.length(); ++i)
                {
                    int tempWidth = 0;
                    TTF_SizeText(font, word.substr(0, i + 1).c_str(), &tempWidth, nullptr);
                    if (tempWidth + x > width)
                    {
                        cutIndex = i;
                        break;
                    }
                }

                std::string visiblePart = word.substr(0, cutIndex);
                Texture(visiblePart, font, renderer, x, y).draw(renderer);

                y += h;
                x = space_size_x;

                word = word.substr(cutIndex);
                TTF_SizeText(font, word.c_str(), &w, &h);
            }

            if (!word.empty())
            {
                Texture(word, font, renderer, x, y).draw(renderer);
                x += w;
            }
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

    const SDL_Rect r{x, y, w, h};

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderFillRect(renderer, &r);
}
