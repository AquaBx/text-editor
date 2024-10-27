//
// Created by tomch on 14/10/2024.
//

#include "Renderer.h"
#include "../Debug/Debug.h"


Renderer::Renderer(const int width, const int height) : width(width), height(height)
{
    //const char* fontPath = "resources/OpenSans.ttf";
    const char* fontPath = "resources/AzeretMono.ttf";

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
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

void Renderer::drawText(std::string text, size_t cursorStart, size_t cursorEnd, float font_scale) const
{
    int x = 0;
    int y = 0;

    int space_size_x = 0;
    int space_size_y = 0;
    TTF_SetFontSize(font, static_cast<int>(30 * font_scale));
    TTF_SizeText(font, " ", &space_size_x, &space_size_y);

    char last = '\r';

    while (!text.empty())
    {
        int w = 0;
        int h = space_size_y;
        int newLine = true;

        std::size_t retour = text.find('\n');
        std::string ligne;
        if (retour != std::string::npos)
        {
            ligne = text.substr(0, retour) + "\r";
            text = text.erase(0, retour + 1);
        }
        else
        {
            ligne = text;
            text = "";
        }

        if ((ligne.empty() || ligne.starts_with('\r')) && cursorStart == x + 1 && cursorEnd == x + 1)
        {
            drawCursor(0, y + space_size_y, 0, space_size_y);
        }
        else
        {
            last = ligne.back();
        }

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
                x = 0;
                if (!newLine)
                {
                    y += h;
                }

                if (w > width)
                {
                    std::string tmpWord;
                    do
                    {
                        tmpWord = word.back() + tmpWord;
                        word.pop_back();
                        TTF_SizeText(font, word.c_str(), &w, &h);
                    }
                    while (w + x > width);
                    ligne = tmpWord + ligne;
                }
            }

            if (cursorStart <= 0 + word.length() - static_cast<int>(word.ends_with("\r")))
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
            newLine = false;
        }
        y += h;
        x = 0;
    }

    if (text.empty() && cursorStart == x && cursorEnd == x && last == '\r')
    {
        drawCursor(0, y, 0, space_size_y);
    }
}

void Renderer::render() const
{
    SDL_RenderPresent(renderer);
}

void Renderer::drawCursor(int x, const int y, int w, const int h) const
{
    if (w == 0)
    {
        w = 4;
        x -= w / 2;
    }

    const SDL_Rect r{x, y, w, h};

    SDL_SetRenderDrawColor(renderer, 128, 192, 255, 255);
    SDL_RenderFillRect(renderer, &r);
}
