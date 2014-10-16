#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "colours.h"

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer){
    SDL_Texture* texture = NULL;

    SDL_Surface* temp = IMG_Load(path);
    if (temp == NULL){
        fprintf(stderr, "SDL_image load failed: %s\n", IMG_GetError());
        return NULL;
    }
    SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0,0,0));

    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (texture == NULL){
        fprintf(stderr, "SDL texture failed: %s\n", SDL_GetError());
        return NULL;
    } 

    SDL_FreeSurface(temp);
    return texture;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    time_t lastTime = NULL;
    time_t thisTime = NULL;
    int hue = 0;

    // Init sdl and check for validity
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL initialisation failed: %s\n", SDL_GetError());
        return 1;
    }
    // Init img and check for validity
    if (IMG_Init(IMG_INIT_PNG) ^ IMG_INIT_PNG){
        fprintf(stderr, "IMG initialisation failed: %s\n", IMG_GetError());
        return 1;
    }

    // Let's get a window
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

    // We have a valid window now. Let's create a renderer.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL){
        fprintf(stderr, "SDL renderer creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Load our texture
    texture = loadTexture("popura.png", renderer);
    if (texture == NULL){
        fprintf(stderr, "Couldn't load texture");
        SDL_Quit();
        return 1;
    }

    // Loop and handle events
    SDL_Event event;
    bool running = true;
    while (running){
        while (SDL_PollEvent(&event) != 0){
            if (event.type == SDL_QUIT){
                running = false;
            }
            else if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
            else {}
        }

        time(&thisTime);
        if (thisTime != lastTime){
            lastTime = thisTime;
            hue = rand() % numColours;
        }

        // Draw
        SDL_RenderClear(renderer);
        SDL_SetTextureColorMod(texture, colourValues[hue][0],colourValues[hue][1],colourValues[hue][2]);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(30);  // About 30 FPS
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

