#ifndef ROBOT_H
    #define ROBOT_H

    #include <vectors.h>

    typedef enum {
        LEFT, UP, RIGHT, DOWN
    } Directions;

    // extern const Vector DIR_VECTORS[4]; // corresponds to enum Directions

    typedef struct {
        Vector pos;
        Directions dir;
        int held_markers;
    } Robot;

    void forward(Robot* robot, char grid[], Vector grid_size);

    void left(Robot* robot);

    void right(Robot* robot);

    int atMarker(Vector pos, char grid[], Vector grid_size);

    int canMoveForward(Vector pos_after_movement, char grid[], Vector grid_size);

    void pickUpMarker(Robot* robot, char grid[], Vector grid_size);

    void dropMarker(Robot* robot, char grid[], Vector grid_size);

    int markerCount(Robot* robot);

#endif