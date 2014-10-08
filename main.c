#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimensions
const int width = 640;
const int depth = 480;

int main(int argc, char* argv[]){
    SDL_Window* window = NULL;
    SDL_Surface* screenSurf = NULL;

    // Init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL initialisation failed: %s\n", SDL_GetError());
    }

    else {
        // Window creation was a success
        window = SDL_CreateWindow(
            "Babby's farced window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, depth,
            SDL_WINDOW_SHOWN
        );

        if (window == NULL) {
            fprintf(stderr, "SDL window creation failed: %s\n", SDL_GetError());
        }

        else {
            screenSurf = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurf, NULL, SDL_MapRGB(screenSurf->format, 0xff, 0x00, 0xff));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}
