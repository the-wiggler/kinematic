////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   - Copyright (c) 2025 Tyler Wiggins. All Rights Reserved. -                                                           //
  //   - This program is free to use for educational purposes. -                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "InitializePath.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   start of the program                                                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    bool running = true;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("KINEMATIC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // load font
    TTF_Font* arial = TTF_OpenFont("assets/arial.ttf", 24);
    if (!arial) printf("Failed to load font: %s\n", TTF_GetError());

    // create text
    SDL_Color white = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(arial, "KINEMATIC!", white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // get text dimensions and position it

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {20, 20, textWidth, textHeight}; // Position at top-left with some margin

    // RUNS THE PATH CALCULATIONS --> IMPORTANT
    InitializePath pathInit;
    pathInit.boundsInitialize();
    pathInit.projectileArrayInitialize();
    pathInit.projectileArrayScale();
    for (int i = 0; i < PATH_RESOLUTION; i++) {std::cout << "[" << i << "] " << pathInit.path_array_x[i] << std::endl;}

    // creates a texture that that points can be rendered on
    SDL_Texture* pathTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    SDL_SetRenderTarget(renderer, pathTexture);

    // maps the points for the projectile on the screen
    for (int i = 0; i < PATH_RESOLUTION; i++) {
        SDL_RenderClear(renderer);

        // renders the rectangles to pathTexture
        SDL_SetRenderTarget(renderer, pathTexture);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect pointRect = {static_cast<int>(pathInit.path_array_x[i]), static_cast<int>(-pathInit.path_array_y[i] + WINDOW_SIZE_Y / 2), 1, 1}; // you need the negative in front of path array since there's a stupid coordinate system
        SDL_RenderFillRect(renderer, &pointRect);

        // resets the renderer to display to the window
        SDL_SetRenderTarget(renderer, NULL);

        // displays pathTexture
        SDL_RenderCopy(renderer, pathTexture, NULL, NULL);

        // displays textTexture
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // displays a leading rectangle that acts as the "projectile"
        if (i < PATH_RESOLUTION - 1) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_Rect leadingPointRect = {static_cast<int>(pathInit.path_array_x[i]), static_cast<int>(-pathInit.path_array_y[i] + WINDOW_SIZE_Y / 2), 3, 3};
            SDL_RenderFillRect(renderer, &leadingPointRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(5);
    }

    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, pathTexture);

    // the impact point (assumes the final element of path_array is the ending - it should be because of the element that was added in projectileScaleArray)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect end_rect = {static_cast<int>(pathInit.path_array_x[PATH_RESOLUTION]), static_cast<int>(pathInit.path_array_y[PATH_RESOLUTION] + WINDOW_SIZE_Y / 2), 3, 3};
    SDL_RenderFillRect(renderer, &end_rect);
    
    // the max height reached
    int max_index = 0;
    for (int i = 1; i < PATH_RESOLUTION; i++) { if (pathInit.path_array_y[i] > pathInit.path_array_y[max_index]) { max_index = i; } }
    double max_x = pathInit.path_array_x[max_index];
    double max_y = pathInit.path_array_y[max_index];
    SDL_SetRenderDrawColor(renderer, 255, 204, 0, 255);
    SDL_Rect max_rect = {static_cast<int>(max_x), static_cast<int>(-max_y + WINDOW_SIZE_Y / 2), 3, -3};
    SDL_RenderFillRect(renderer, &max_rect);

    // resets the renderer to display to the window
    SDL_SetRenderTarget(renderer, NULL);

    // displays pathTexture
    SDL_RenderCopy(renderer, pathTexture, NULL, NULL);

    // displays textTexture
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
   
    SDL_RenderPresent(renderer);
    
    

    // keeps window open
    SDL_Event e; bool quit = false; 
    while (!quit) {if (SDL_WaitEvent(&e)) {if (e.type == SDL_QUIT) quit = true;}}

    // clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(pathTexture);
    TTF_CloseFont(arial);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
