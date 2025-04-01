////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   - Copyright (c) 2025 Tyler Wiggins. All Rights Reserved. -                                                           //
  //   - This program is free to use for educational purposes. -                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <cstring>
#include <vector>

#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 800
#define PATH_RESOLUTION 200

double initial_velocity = 80;
double initial_angle = 60;
double initial_height = 45;


class InitializePath {
    private:
        double initial_x_velocity, initial_y_velocity, flight_time, 
        max_y_height, max_x_displacement;
        double g = -9.8;

    public: 
        std::vector<double> path_array_x;
        std::vector<double> path_array_y;
        double impact_point[2];

        void boundsInitialize() {

            double initial_angle_rad = initial_angle * (M_PI / 180.0);
            
            initial_x_velocity = initial_velocity * cos(initial_angle_rad); // initial x component of velocity
            initial_y_velocity = initial_velocity * sin(initial_angle_rad); // initial y component of velocity

            std::cout << "initial_x_velocity: " << initial_x_velocity << std::endl;
            std::cout << "initial_y_velocity: " << initial_y_velocity << std::endl;

            if (initial_angle == 0) { // if initial angle is 0, assume no initial y component velocity
                flight_time = sqrt(2 * -initial_height / g);
                max_y_height = initial_height;

            } else if (initial_angle >= -90 && initial_angle <= 90 && initial_angle != 0) { // if initial angle is either > or < 0, assume initial y component is positive or negative respectively
                max_y_height = (-pow(initial_y_velocity, 2) / (2 * g) + initial_height); // maximum height reached
                double max_y_time = -initial_y_velocity / g; // what time it reached max height

                flight_time = (-initial_y_velocity - sqrt(pow(initial_y_velocity, 2) + 2 * g * -initial_height)) / g; // total flight time

                std::cout << "Max height: " << max_y_height << "m | @t = " << max_y_time << std::endl;

            }  else {
                std::cout << "ERROR: INPUT ANGLE OUT OF ACCEPTABLE BOUNDS" << std::endl;
                exit(EXIT_FAILURE);
            }
            
            max_x_displacement = initial_x_velocity * flight_time; // total X distance traveled
            std::cout << "Total flight time: " << flight_time << std::endl;
            std::cout << "Total X distance traveled: " << max_x_displacement << std::endl;
        }

        void projectileArrayInitialize() {
            // resizes the arrays to match the proper resolution for its path
            path_array_x.resize(PATH_RESOLUTION);
            path_array_y.resize(PATH_RESOLUTION);
            if(path_array_x.size() != path_array_y.size()) {std::cout << "ERROR: PATH ARRAY SIZE MISMATCHED" << std::endl;}

            // performs kinematic calculations based on previous data that maps each point. Works as a coordinate system
            float path_counter = 0.0;
            for (int i = 0; i < PATH_RESOLUTION; i++) {
                path_array_x[i] = initial_x_velocity * (path_counter); // writes increments of the x displacement
                path_array_y[i] = (initial_y_velocity * path_counter + 0.5 * g * pow(path_counter, 2)); // writes increments of the y displacement
                path_counter += (flight_time / PATH_RESOLUTION);

            }


            // the points of impact are a separate array, this should eventually be removed and just added onto the end of the path array
            impact_point[0] = initial_x_velocity * flight_time;
            impact_point[1] = initial_height;
        }

        void projectileArrayScale() {
            // scales the arrays to properly fit inside the bounds of the window (kind of works lol)
            if (max_y_height > WINDOW_SIZE_Y / 2 || max_y_height < WINDOW_SIZE_Y / 2) { 
                float y_scale = (WINDOW_SIZE_Y / 2) / max_y_height;
                // scales all y elements in the array
                for (int i = 0; i < PATH_RESOLUTION; i++) {
                    path_array_y[i] *= y_scale;
                    // path_array_y[i] -= 25;
                }
                impact_point[1] *= y_scale;
            }

            if (max_x_displacement > WINDOW_SIZE_X) {
                float x_scale = WINDOW_SIZE_X / max_x_displacement;
                // scales all x elements in the array
                for (int i = 0; i < PATH_RESOLUTION; i++) {
                    path_array_x[i] *= x_scale;
                }
                impact_point[0] *= x_scale;
            } 
        }
};

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

    // run the calculations
    InitializePath pathMain;
    pathMain.boundsInitialize();
    pathMain.projectileArrayInitialize();
    pathMain.projectileArrayScale();
    for (int i = 0; i < PATH_RESOLUTION; i++) {std::cout << "[" << i << "] " << pathMain.path_array_x[i] << std::endl;}

    // creates a texture that that points can be rendered on
    SDL_Texture* pathTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    SDL_SetRenderTarget(renderer, pathTexture);

    // maps the points for the projectile on the screen
    for (int i = 0; i < PATH_RESOLUTION; i++) {
        SDL_RenderClear(renderer);

        // renders the rectangles to pathTexture
        SDL_SetRenderTarget(renderer, pathTexture);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect pointRect = {static_cast<int>(pathMain.path_array_x[i]), static_cast<int>(-pathMain.path_array_y[i] + WINDOW_SIZE_Y / 2), 1, 1}; // you need the negative in front of path array since there's a stupid coordinate system
        SDL_RenderFillRect(renderer, &pointRect);

        // resets the renderer to display to the window
        SDL_SetRenderTarget(renderer, NULL);

        // displays pathTexturewwwwwwwwwwwwwwwwwwwwwwwwwwww
        SDL_RenderCopy(renderer, pathTexture, NULL, NULL);

        // displays textTexture
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // displays a leading rectangle that acts as the "projectile"
        if (i < PATH_RESOLUTION - 1) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_Rect leadingPointRect = {static_cast<int>(pathMain.path_array_x[i]), static_cast<int>(-pathMain.path_array_y[i] + WINDOW_SIZE_Y / 2), 3, 3};
            SDL_RenderFillRect(renderer, &leadingPointRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(5);
    }

    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, pathTexture);

    // the impact point
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect end_rect = {static_cast<int>(pathMain.impact_point[0]), static_cast<int>(pathMain.impact_point[1] + WINDOW_SIZE_Y / 2), 3, 3};
    SDL_RenderFillRect(renderer, &end_rect);
    
    // the max height reached
    int max_index = 0;
    for (int i = 1; i < PATH_RESOLUTION; i++) { if (pathMain.path_array_y[i] > pathMain.path_array_y[max_index]) { max_index = i; } }
    double max_x = pathMain.path_array_x[max_index];
    double max_y = pathMain.path_array_y[max_index];
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
    
    SDL_Event e; bool quit = false; while(quit == false){ while(SDL_PollEvent(&e)){ if(e.type == SDL_QUIT) quit = true; } } // thing that holds the window open. Credit: Lazy Foo' Productions

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
