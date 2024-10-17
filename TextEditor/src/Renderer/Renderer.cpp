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
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

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

void Renderer::drawText(std::string text, size_t cursorStart, size_t cursorEnd) const {
    std::string delimiter = "\n";
    int y = 10;
    int actual_x = 0;

    while (!text.empty()) {
        std::size_t retour = text.find(delimiter);
        std::string ligne;

        if (retour != std::string::npos) {
            ligne = text.substr(0, retour);
            text = text.erase(0, retour + delimiter.length());
        } else {
            ligne = text;
            text = "";
        }

        while (!ligne.empty()) {
            int w = 0, h = 0;
            int char_pos = 0;
            
            while (char_pos < ligne.length()) {
                std::string sub_ligne = ligne.substr(0, char_pos + 1);
                TTF_SizeText(font, sub_ligne.c_str(), &w, &h);

                if (w > width) {
                    std::string ligne_a_afficher = ligne.substr(0, char_pos);

                    Texture(ligne_a_afficher, font, renderer, 0, y).draw(renderer);

                    if (actual_x <= cursorStart && cursorStart <= actual_x + ligne_a_afficher.length()) {
                        if (cursorEnd <= actual_x + ligne_a_afficher.length()) {
                            int ax = 0, aw = 0;
                            TTF_SizeText(font, ligne_a_afficher.substr(0, cursorStart - actual_x).c_str(), &ax, nullptr);
                            TTF_SizeText(font, ligne_a_afficher.substr(cursorStart - actual_x, cursorEnd - cursorStart).c_str(), &aw, nullptr);
                            drawCursor(ax, y, aw, h);
                        }
                    }

                    ligne = ligne.substr(char_pos);
                    actual_x += ligne_a_afficher.length();
                    y += h;
                    char_pos = 0;
                } 
                else {
                    char_pos++;
                }
            }

            if (!ligne.empty()) {
                Texture(ligne, font, renderer, 0, y).draw(renderer);

                if (actual_x <= cursorStart && cursorStart <= actual_x + ligne.length()) {
                    if (cursorEnd <= actual_x + ligne.length()) {
                        int ax = 0, aw = 0;
                        TTF_SizeText(font, ligne.substr(0, cursorStart - actual_x).c_str(), &ax, nullptr);
                        TTF_SizeText(font, ligne.substr(cursorStart - actual_x, cursorEnd - cursorStart).c_str(), &aw, nullptr);
                        drawCursor(ax, y, aw, h);
                    }
                }

                actual_x += ligne.length();
                y += h;
                ligne = "";
            }
        }
    }
}



void Renderer::render() const
{
    SDL_RenderPresent(renderer);
};

void Renderer::drawCursor(int x, int y, int w, int h) const
{
    if (w == 0){
        w = 4;
        x-=w/2;
    }

    SDL_Rect r{x,y,w,h};

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);

    // Render rect
    SDL_RenderFillRect(renderer, &r);
}
