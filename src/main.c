////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   - Copyright (c) 2025 Tyler Wiggins. All Rights Reserved. -                                                           //
  //   - This program is free to use for educational purposes. -                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>  

#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 800

const double g = -9.8;
double initial_velocity, initial_angle, initial_height, 
initial_x_velocity, initial_y_velocity, flight_time, 
max_y_height, max_x_displacement, impact_point[2];

#define PATH_RESOLUTION 400 // how many points will be plotted for the path
double *path_array_x; 
double *path_array_y;

// initializes the boundaries of the operation by calculating start/max/min of the projectile
void boundsInitialize() {

      initial_velocity = 300;
    initial_angle = 70;
    initial_height = 0;

    double initial_angle_rad = initial_angle * (M_PI / 180.0);
    
    initial_x_velocity = initial_velocity * cos(initial_angle_rad); // initial x component of velocity
    initial_y_velocity = initial_velocity * sin(initial_angle_rad); // initial y component of velocity

    printf("initial_x_velocity: %lf m/s\n", initial_x_velocity);
    printf("initial_y_velocity: %lf m/s\n", initial_y_velocity);

    if (initial_angle == 0) { // if initial angle is 0, assume no initial y component velocity
        flight_time = sqrt(2 * -initial_height / g);
        max_y_height = initial_height;

    } else if (initial_angle >= -90 && initial_angle <= 90 && initial_angle != 0) { // if initial angle is either > or < 0, assume initial y component is positive or negative respectively
        max_y_height = (-pow(initial_y_velocity, 2) / (2 * g) + initial_height); // maximum height reached
        double max_y_time = -initial_y_velocity / g; // what time it reached max height

        flight_time = (-initial_y_velocity - sqrt(pow(initial_y_velocity, 2) + 2 * g * -initial_height)) / g; // total flight time

        printf("Max height: %lf m | @t = %lf s\n", max_y_height, max_y_time);

    }  else {
        printf("ERROR: INPUT ANGLE OUT OF ACCEPTABLE BOUNDS\n");
        exit(EXIT_SUCCESS);
    }
    
    max_x_displacement = initial_x_velocity * flight_time; // total X distance traveled
    printf("Total flight time: %lf s\n", flight_time);
    printf("Total X distance traveled: %lf m\n", max_x_displacement);
}

void projectileArrayInitialize() {
        // creates the arrays for the projectile's path
    path_array_x = (double*)malloc(PATH_RESOLUTION * sizeof(double)); // arrays that hold coordinate values for the position of the object in motion
        if (path_array_x == NULL) {printf("ERROR: MEMORY ALLOCATION FAILED FOR 'path_array_x'!\n"); exit(1);}
    path_array_y = (double*)malloc(PATH_RESOLUTION * sizeof(double)); // these two arrays should always be the same size
        if (path_array_y == NULL) {printf("ERROR: MEMORY ALLOCATION FAILED FOR 'path_array_y'!\n"); exit(1);}

    float path_counter = 0.0;
    for (int i = 0; i < PATH_RESOLUTION; i++) {
        path_array_x[i] = initial_x_velocity * (path_counter); // writes increments of the x displacement
        path_array_y[i] = (initial_y_velocity * path_counter + 0.5 * g * pow(path_counter, 2)); // writes increments of the y displacement
        path_counter += (flight_time / PATH_RESOLUTION);

    }
    impact_point[0] = initial_x_velocity * flight_time;
    impact_point[1] = initial_height;

    // scales the arrays to properly fit inside the bounds of the window (kind of works lol)
    if (max_y_height > WINDOW_SIZE_Y / 2 || max_y_height < WINDOW_SIZE_Y / 2) { 
        float y_scale = (WINDOW_SIZE_Y / 2) / max_y_height;
        for (int i = 0; i < PATH_RESOLUTION; i++) { // scales all y elements in the array
            path_array_y[i] *= y_scale;
            // path_array_y[i] -= 25;
        }
        impact_point[1] *= y_scale;
    }

    if (max_x_displacement > WINDOW_SIZE_X) {
        float x_scale = WINDOW_SIZE_X / max_x_displacement;
        for (int i = 0; i < PATH_RESOLUTION; i++) { // scales all x elements in the array
            path_array_x[i] *= x_scale;
        }
        impact_point[0] *= x_scale;
    } 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   start of the program                                                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("KINEMATIC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Load font
    TTF_Font* arial = TTF_OpenFont("assets/arial.ttf", 24);
    if (!arial) printf("Failed to load font: %s\n", TTF_GetError());

    // Create text
    SDL_Color white = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(arial, "KINEMATIC!", white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get text dimensions and position it

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {20, 20, textWidth, textHeight}; // Position at top-left with some margin

    // run the calculations
    boundsInitialize(); 
    projectileArrayInitialize();

    // creates a texture that that points can be rendered on
    SDL_Texture* pathTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    SDL_SetRenderTarget(renderer, pathTexture);

    // maps the points for the projectile on the screen
    for (int i = 0; i < PATH_RESOLUTION; i++) {
        SDL_RenderClear(renderer);

        // renders the rectangles to pathTexture
        SDL_SetRenderTarget(renderer, pathTexture);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect pointRect = {path_array_x[i], -path_array_y[i] + WINDOW_SIZE_Y / 2, 1, 1}; // you need the negative in front of path array since there's a stupid coordinate system
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
            SDL_Rect leadingPointRect = {path_array_x[i], -path_array_y[i] + WINDOW_SIZE_Y / 2, 3, 3};
            SDL_RenderFillRect(renderer, &leadingPointRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, pathTexture);

    // the impact point
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect end_rect = {impact_point[0], impact_point[1] + WINDOW_SIZE_Y / 2, 3, 3};
    SDL_RenderFillRect(renderer, &end_rect);
    
    // the max height reached
    int max_index = 0;
    for (int i = 1; i < PATH_RESOLUTION; i++) { if (path_array_y[i] > path_array_y[max_index]) { max_index = i; } }
    double max_x = path_array_x[max_index];
    double max_y = path_array_y[max_index];
    SDL_SetRenderDrawColor(renderer, 255, 204, 0, 255);
    SDL_Rect max_rect = {max_x, -max_y + WINDOW_SIZE_Y / 2, 3, -3};
    SDL_RenderFillRect(renderer, &max_rect);

    // resets the renderer to display to the window
    SDL_SetRenderTarget(renderer, NULL);

    // displays pathTexture
    SDL_RenderCopy(renderer, pathTexture, NULL, NULL);

    // displays textTexture
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
   
    SDL_RenderPresent(renderer);

    free(path_array_x);
    free(path_array_y);
    
    SDL_Event e; bool quit = false; while(quit == false){ while(SDL_PollEvent(&e)){ if(e.type == SDL_QUIT) quit = true; } } // thing that holds the window open. Credit: Lazy Foo' Productions

    // Clean up
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