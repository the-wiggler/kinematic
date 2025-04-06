#ifndef INITIALIZE_PATH_H
#define INITIALIZE_PATH_H

#include <vector>
#include <iostream>
#include <cstdlib>

#define PATH_RESOLUTION 200
#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 800

extern double initial_angle;
extern double initial_height;

class InitializePath {
    private: 
        double initial_x_velocity, initial_y_velocity, flight_time, 
        max_y_height, max_x_displacement;
        double g = -9.8;

    public:
        double initial_velocity;
        double initial_angle;
        double initial_height;

        std::vector<double> path_array_x;
        std::vector<double> path_array_y;

        void boundsInitialize();
        void projectileArrayInitialize();
        void projectileArrayScale();
}; 

#endif 