#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Screen dimensions
const int width = 640;
const int depth = 480;

int main(int argc, char* argv[]){
    SDL_Window* window = NULL;
    SDL_Surface* screenSurf = NULL;

    // Init sdl and check for validity
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL initialisation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Window creation was a success
    window = SDL_CreateWindow(
        "0x40 Hues - Desktop Edition",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, depth,
        SDL_WINDOW_FULLSCREEN_DESKTOP
    );
    if (window == NULL) {   // Check it worked
        fprintf(stderr, "SDL window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // We have a valid window now. Get the backing surface and paint it
    screenSurf = SDL_GetWindowSurface(window);
    srand(time(NULL));
    
    for (int i = 0; i < 20; i++){
        uint8_t r = (uint8_t) rand()*255;
        uint8_t g = (uint8_t) rand()*255;
        uint8_t b = (uint8_t) rand()*255;
        SDL_FillRect(screenSurf, NULL, SDL_MapRGB(screenSurf->format, r,g,b));
        SDL_UpdateWindowSurface(window);
        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
