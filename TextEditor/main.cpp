/*
Render text.
Based on SDL_ttf, which is has a separate source tree
https://www.libsdl.org/projects/SDL_ttf/, but is packaged
together with SDL on Debian
*/

#include <stdlib.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "src/Client/Client.h"

int main() {
/*

    SDL_Event event;
    SDL_Rect rect1, rect2;
    SDL_Texture *texture1, *texture2;

    int quit;

    Renderer myRenderer(800,800);

    char text1[] = "hello";
    char text2[] = "world";

    get_text_and_rect(myRenderer.getRenderer(), 0, 0, text1, myRenderer.getFont(), &texture1, &rect1);
    get_text_and_rect(myRenderer.getRenderer(), 0, rect1.y + rect1.h, text2, myRenderer.getFont(), &texture2, &rect2);
    quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderCopy(myRenderer.getRenderer(), texture1, NULL, &rect1);
        SDL_RenderCopy(myRenderer.getRenderer(), texture2, NULL, &rect2);
        SDL_RenderPresent(myRenderer.getRenderer());
    }*/

    /* Deinit TTF. */
    /*
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
*/

    Client myClient(800,800);
    myClient.run();
    return EXIT_SUCCESS;
}

int WinMain(int argc, char **argv){
    return main();
}