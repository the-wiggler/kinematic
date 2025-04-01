////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   - Copyright (c) 2025 Tyler Wiggins. All Rights Reserved. -                                                           //
  //   - This program is free to use for educational purposes. -                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
#include <cmath>
#include <cstring>
#include <vector>

#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 800
#define PATH_RESOLUTION 400

double initial_velocity = 300;
double initial_angle = 70;
double initial_height = 0;


class InitializePath {
    private:
        double initial_x_velocity, initial_y_velocity, flight_time, 
        max_y_height, max_x_displacement, impact_point[2];
        double g = -9.8;

    public: 
        std::vector<double> path_array_x;
        std::vector<double> path_array_y;
        path_array_x.resize(PATH_RESOLUTION);
        path_array_y.resize(PATH_RESOLUTION);

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
            // creates the arrays for the projectile's path
            if(path_array_x.size() != path_array_y.size()) {std::cout << "ERROR: PATH ARRAY SIZE MISMATCHED" << std::endl;}

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

};

int main(int argc, char *argv[]) {
    InitializePath pathMain;
    pathMain.boundsInitialize();
    pathMain.projectileArrayInitialize();
    for (int i = 0; i < PATH_RESOLUTION; i++) {std::cout << pathMain.path_array_x[i] << std::endl;}
    return 0;
}



