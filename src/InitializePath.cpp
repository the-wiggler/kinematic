#include <cmath>
#include <vector>
#include "InitializePath.h"

void InitializePath::boundsInitialize() {
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


void InitializePath::projectileArrayInitialize() {
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

    path_array_x.push_back(initial_x_velocity * flight_time);
    path_array_y.push_back(initial_height);
	}


// scales each path array so that it fits inside the screen (retains aspect ratio)
void InitializePath::projectileArrayScale() {
    if (max_x_displacement > WINDOW_SIZE_X || max_y_height > WINDOW_SIZE_Y) {
        float x_scale = WINDOW_SIZE_X / max_x_displacement * 0.98;
        float y_scale = (WINDOW_SIZE_Y / 2) / max_y_height;

        float path_scale_factor = std::min(x_scale, y_scale);

        for (int i = 0; i < PATH_RESOLUTION; i++) {
            path_array_x[i] *= path_scale_factor;
            path_array_y[i] *= path_scale_factor;
        }

        path_array_x[path_array_x.size() - 1] *= path_scale_factor;
        path_array_y[path_array_y.size() - 1] *= path_scale_factor;
    }
}
