#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* loadSurface(const char* path, SDL_PixelFormat* format){
    SDL_Surface* finalSurface = NULL;

    SDL_Surface* temp = IMG_Load(path);
    if (temp == NULL){
        fprintf(stderr, "SDL_image load failed: %s\n", IMG_GetError());
        return NULL;
    }

    finalSurface = SDL_ConvertSurface(temp, format, 0);
    if (finalSurface == NULL){
        fprintf(stderr, "SDL_image conversion failed: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_SetColorKey(finalSurface, SDL_TRUE, SDL_MapRGB(finalSurface->format, 0,0,0));

    SDL_FreeSurface(temp);
    return finalSurface;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    SDL_Window* window = NULL;
    SDL_Surface* screenSurf = NULL;
    SDL_Surface* testImage = NULL;

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
        800, 600,                       // boring dimensions
        SDL_WINDOW_FULLSCREEN_DESKTOP
    );
    if (window == NULL) {   // Check it worked
        fprintf(stderr, "SDL window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // We have a valid window now. Lets load the surfaces for window and image
    screenSurf = SDL_GetWindowSurface(window);
    testImage = loadSurface("test_mask.png", screenSurf->format);

    // Now lets color and write
    SDL_FillRect(screenSurf, 0, SDL_MapRGB(screenSurf->format, 0xFF, 0x00, 0xFF));
    SDL_BlitSurface(testImage, NULL, screenSurf, NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

