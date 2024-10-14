//
// Created by tomch on 14/10/2024.
//

#include "Renderer.h"

/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void get_text_and_rect(SDL_Renderer *renderer, int x, int y, std::string text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {

}

Renderer::Renderer(int width, int height) : width(width), height(height) {
    const char * fontPath = "resources/OpenSans.ttf";

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    TTF_Init();

    font = TTF_OpenFont(fontPath, 24);

    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void Renderer::resize() {

}

Renderer::~Renderer() {
    SDL_DestroyTexture(texture);

    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::drawText(std::string text){

    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);

    rect->x = 0;
    rect->y = 0;
    rect->w = text_width;
    rect->h = text_height;

    SDL_RenderCopy(renderer, texture, NULL, rect);
}

void Renderer::render(){
    SDL_RenderPresent(renderer);
};