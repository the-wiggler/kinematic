////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   - Copyright (c) 2025 Tyler Wiggins. All Rights Reserved. -                                                           //
  //   - This program is free to use for educational purposes. -                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <math.h>  

int i;

double initial_velocity, initial_angle, initial_height, initial_x_velocity, initial_y_velocity, flight_time, max_y_height, max_x_displacement;
int path_resolution;
const double g = -9.8;
const int window_size_x = 1000;
const int window_size_y = 800;

// initializes the boundaries of the operation by calculating start/max/min of the projectile
void boundsInitialize() { 
    
    printf("Initial Velocity: ");
        scanf("%lf", &initial_velocity);
    printf("Intial Angle: ");
        scanf("%lf", &initial_angle);
    printf("Initial Height: ");
        scanf("%lf", &initial_height);

    double initial_angle_rad = initial_angle * (M_PI / 180.0);
    
    initial_x_velocity = initial_velocity * cos(initial_angle_rad); // initial x component of velocity
    initial_y_velocity = initial_velocity * sin(initial_angle_rad); // initial y component of velocity

    printf("initial_x_velocity: %lf m/s\n", initial_x_velocity);
    printf("initial_y_velocity: %lf m/s\n", initial_y_velocity);

    if (initial_angle == 0) { // if initial angle is 0, assume no initial y component velocity
        flight_time = sqrt(2 * -initial_height / g);
        max_y_height = initial_height;
        printf("Total flight time: %lf s\n", flight_time);

    } else if (initial_angle >= -90 && initial_angle <= 90 && initial_angle != 0) { // if initial angle is either > or < 0, assume initial y component is positive or negative respectively
        max_y_height = (-pow(initial_y_velocity, 2) / (2 * g) + initial_height); // maximum height reached
        double max_y_time = -initial_y_velocity / g; // what time it reached max height
        printf("Max height: %lf m | @t = %lf s\n", max_y_height, max_y_time);

        flight_time = (-initial_y_velocity - sqrt(pow(initial_y_velocity, 2) + 2 * g * -initial_height)) / g; // total flight time
        printf("Total flight time: %lf s\n", flight_time);
    }  else {
        printf("ERROR: INPUT ANGLE OUT OF ACCEPTABLE BOUNDS\n");
    }
    
    max_x_displacement = initial_x_velocity * flight_time; // total X distance traveled
    printf("Total X distance traveled: %lf m\n", max_x_displacement);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   start of the program                                                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SDL_main(int argc, char *argv[]);


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("KINEMATIC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size_x, window_size_y, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Load font
    TTF_Font* arial = TTF_OpenFont("assets/arial.ttf", 24);
    (!arial) ? printf("Failed to load font: %s\n", TTF_GetError()) : (void)0;

    // Create text
    SDL_Color white = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(arial, "Hello World!", white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get text dimensions and position it

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {20, 20, textWidth, textHeight}; // Position at top-left with some margin

    // run the kinematics calculations
    boundsInitialize(); 
    
    // creates the arrays for the projectile's path
    path_resolution = 150;
    double *path_array_x = (double*)malloc(path_resolution * sizeof(double)); // arrays that hold coordinate values for the position of the object in motion
        path_array_x[path_resolution - 1] = initial_x_velocity * flight_time; // total X distance traveled
    double *path_array_y = (double*)malloc(path_resolution * sizeof(double)); // these two arrays should always be the same size
        path_array_y[path_resolution - 1] = -initial_height;

    double path_counter = 0.0;
    for (i = 0; i < path_resolution - 1; i++) {
        path_array_x[i] = initial_x_velocity * (path_counter); // writes increments of the x displacement
        path_array_y[i] = (initial_y_velocity * path_counter + 0.5 * g * pow(path_counter, 2)); // writes increments of the y displacement
        path_counter += (flight_time / path_resolution);
    }

    // scales the array to properly fit inside the bounds of the window (kind of works lol)
    if (max_y_height > window_size_y / 2) { 
        float y_scale = (window_size_y / 2) / max_y_height;
        for (i = 0; i < path_resolution; i++) { // scales all y elements in the array
            path_array_y[i] *= y_scale;
            path_array_y[i] -= 25;
        }
    }

    if (max_x_displacement > window_size_x) {
        float x_scale = window_size_x / max_x_displacement;
        for (i = 0; i < path_resolution; i++) { // scales all x elements in the array
            path_array_x[i] *= x_scale;
            path_array_x[i] -= 25;
        }
    }

    // Draw points
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // maps the points for the projectile on the screen
    for (i = 0; i < path_resolution; i++) { 
        SDL_Rect pointRect = {path_array_x[i], -path_array_y[i] + window_size_y / 2, 3, 3}; // you need the negative in front of path array since there's a stupid coordinate system
        SDL_RenderFillRect(renderer, &pointRect);
    }

    // the impact point
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect end_rect = {path_array_x[path_resolution - 1], -path_array_y[path_resolution - 1] + window_size_y / 2, 5, 5};
    SDL_RenderFillRect(renderer, &end_rect);
    
    // the max height reached
    int max_index = 0;
    for (i = 1; i < path_resolution; i++) { if (path_array_y[i] > path_array_y[max_index]) { max_index = i; } }
    double max_x = path_array_x[max_index];
    double max_y = path_array_y[max_index];
    SDL_SetRenderDrawColor(renderer, 0, 150, 150, 255);
    SDL_Rect max_rect = {max_x, -max_y + window_size_y / 2, 3, 3};
    SDL_RenderFillRect(renderer, &max_rect);

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    free(path_array_x);
    free(path_array_y);

    SDL_RenderPresent(renderer);
    
    SDL_Event e; bool quit = false; while(quit == false){ while(SDL_PollEvent(&e)){ if(e.type == SDL_QUIT) quit = true; } } // thing that holds the window open. Credit: Lazy Foo' Productions
    
    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(arial);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}


