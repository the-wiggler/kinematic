#include <SDL2/SDL.h>
#include <stdbool.h>

int main() {
    int i;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("KINEMATIC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Draw a point
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (i = 0; i < 10; i++) {
        SDL_RenderDrawPoint(renderer, 320, 240 + 10 * i);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    
    SDL_Event e; bool quit = false; while(quit == false){ while(SDL_PollEvent(&e)){ if(e.type == SDL_QUIT) quit = true; } } // thing that holds the window open. Credit: Lazy Foo' Productions
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}


