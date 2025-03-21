#include <stdio.h>
#include <math.h>

// s = (u + v) / t + 2
// v = u + a * t
// s = u * t + 0.5 * a * t^2
// v^2 = u^2 + 2 * a * s

int main() {
    double u; // initial velocity
    double iniAngle; // inital angle
    double iniH; // initial height
    const double g = -9.8;
    
    printf("Initial Velocity: ");
        scanf("%lf", &u);
    printf("Intial Angle: ");
        scanf("%lf", &iniAngle);
    printf("Initial Height: ");
        scanf("%lf", &iniH);

    double iniAngleRad = iniAngle * (M_PI / 180.0);
    
    double uX = u * cos(iniAngleRad); // initial x component of velocity
    double uY = u * sin(iniAngleRad); // initial y component of velocity

    printf("uX: %lf m/s\n", uX);
    printf("uY: %lf m/s\n", uY);

    double flightTime;

    if (iniAngle == 0) { // if initial angle is 0, assume no initial y component velocity
        flightTime = sqrt(2 * -iniH / g);
        printf("Total flight time: %lf s\n", flightTime);

    } else { // if initial angle is either > or < 0, assume initial y component is positive or negative respectively
        double maxS = (-pow(uY, 2) / (2 * g) + iniH); // maximum height reached
        double maxStime = -uY / g; // what time it reached max height
        printf("Max height: %lf m | @t = %lf s\n", maxS, maxStime);

        flightTime = (-uY - sqrt(pow(uY, 2) + 2 * g * -iniH)) / g; // total flight time
        printf("Total flight time: %lf s\n", flightTime);

    } 
    double fX = uX * flightTime; // total X distance traveled
    printf("Total X distance traveled: %lf m\n", fX);

    ////////////////////////

    int pathRes = 50;
    double pathArrayX[pathRes]; // arrays that hold coordinate values for the position of the object in motion
    pathArrayX[pathRes - 1] = uX * flightTime; // total X distance traveled
    double pathArrayY[pathRes]; // these two arrays should always be the same size
    pathArrayY[pathRes - 1] = -iniH;

    int i;
    double pathTimeCounter = 0.0;
    for (i = 0; i < pathRes - 1; i++) {
        pathArrayX[i] = uX * (pathTimeCounter); // writes increments of the x displacement
        pathArrayY[i] = (uY * pathTimeCounter + 0.5 * g * pow(pathTimeCounter, 2)); // writes increments of the y displacement
        pathTimeCounter += (flightTime / pathRes);
    }
    for (i = 0; i < pathRes; i++) {printf("%lf, %lf\n", pathArrayX[i], pathArrayY[i]); }

    FILE *file = fopen("trajectory.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "X (m), Y (m)\n");
    for (int i = 0; i < pathRes; i++) {
        fprintf(file, "%lf, %lf\n", pathArrayX[i], pathArrayY[i]);
    }
    
    fclose(file);
    printf("Data written to trajectory.csv\n");

    return 0;
}
