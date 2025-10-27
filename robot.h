#ifndef ROBOT_H
    #define ROBOT_H

    #include "vectors.h"

    typedef enum directions {
        LEFT, UP, RIGHT, DOWN
    } Directions;

    typedef struct robot {
        Vector pos;
        Directions dir;
        int held_markers;
    } Robot;

    void forward(Robot* robot, char grid[], int grid_size_x, int grid_size_y);

    void left(Robot* robot);

    void right(Robot* robot);

    int atMarker(Vector position);

    int canMoveForward(Vector pos_after_movement, char grid[], int grid_size_x, int grid_size_y);

    void pickUpMarker(Robot* robot, char grid[], int grid_size_x, int grid_size_y);

    void dropMarker(Robot* robot, char grid[], int grid_size_x, int grid_size_y);

    int markerCount(Robot* robot);

#endif