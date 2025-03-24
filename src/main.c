////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   - Copyright (c) 2025 Tyler Wiggins. All Rights Reserved. -                                                           //
  //   - This program is free to use for educational purposes. -                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>  

int i;

double initial_velocity, initial_angle, initial_height, initial_x_velocity, initial_y_velocity, flight_time, max_y_height, max_x_displacement;
int path_resolution;
float x_scale, y_scale;
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

    } else { // if initial angle is either > or < 0, assume initial y component is positive or negative respectively
        max_y_height = (-pow(initial_y_velocity, 2) / (2 * g) + initial_height); // maximum height reached
        double max_y_time = -initial_y_velocity / g; // what time it reached max height
        printf("Max height: %lf m | @t = %lf s\n", max_y_height, max_y_time);

        flight_time = (-initial_y_velocity - sqrt(pow(initial_y_velocity, 2) + 2 * g * -initial_height)) / g; // total flight time
        printf("Total flight time: %lf s\n", flight_time);

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
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // run the kinematics calculations
    boundsInitialize(); 
    

    //creates the arrays for the projectile's path

    path_resolution = 50;

    double path_array_x[path_resolution]; // arrays that hold coordinate values for the position of the object in motion
        path_array_x[path_resolution - 1] = initial_x_velocity * flight_time; // total X distance traveled
    double path_array_y[path_resolution]; // these two arrays should always be the same size
        path_array_y[path_resolution - 1] = -initial_height;

    double path_counter = 0.0;
    for (i = 0; i < path_resolution - 1; i++) {
        path_array_x[i] = initial_x_velocity * (path_counter); // writes increments of the x displacement
        path_array_y[i] = (initial_y_velocity * path_counter + 0.5 * g * pow(path_counter, 2)); // writes increments of the y displacement
        path_counter += (flight_time / path_resolution);
    }

    for (i = 0; i < path_resolution; i++) {printf("%lf, %lf\n", path_array_x[i], path_array_y[i]); }


    // scales the array to properly fit inside the bounds of the window (does not work lol)
 
    // float x_range = max_x_displacement;
    // float y_range = max_y_height + initial_height;

    // x_scale = x_range / window_size_x;
    // y_scale = y_range / window_size_y;

    // float scale = (x_scale < y_scale) ? x_scale : y_scale;

    // for (int i = 0; i < path_resolution; i++) {
    //     path_array_x[i] = 10 + (path_array_x[i]) * scale;
    //     path_array_y[i] = window_size_y - 50 - (path_array_y[i]) * scale;
    // }
    // for (i = 0; i < path_resolution; i++) {printf("%lf, %lf\n", path_array_x[i], path_array_y[i]); }


    // Draw points

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (i = 0; i < path_resolution; i++) { 
        SDL_Rect pointRect = {10 + path_array_x[i], 500 + -path_array_y[i], 3, 3};
        SDL_RenderFillRect(renderer, &pointRect);
    }
    SDL_RenderPresent(renderer);
    
    SDL_Event e; bool quit = false; while(quit == false){ while(SDL_PollEvent(&e)){ if(e.type == SDL_QUIT) quit = true; } } // thing that holds the window open. Credit: Lazy Foo' Productions
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}


