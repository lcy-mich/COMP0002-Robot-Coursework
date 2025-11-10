#ifndef ROBOT_H

    #define ROBOT_H

    #include <vectors.h>
    #include <grid.h>

    typedef struct {
        Vector pos;
        Directions dir;
        int held_markers;
        Vector current_target;
    } Robot;

    void forward(Robot* robot, int grid[], Vector grid_size);

    void left(Robot* robot);

    void right(Robot* robot);

    int atMarker(Robot robot, int grid[], Vector grid_size);

    int canMoveForward(Robot robot, int grid[], Vector grid_size);

    void pickUpMarker(Robot* robot, int grid[], Vector grid_size);

    void dropMarker(Robot* robot, int grid[], Vector grid_size);

    int markerCount(Robot* robot);

#endif