#ifndef GRID_H
    #define GRID_H

    #include "../inc/vectors.h"

    typedef enum {
        AIR, WALL, MARKER
    } GridObjects;


    GridObjects getObjectAtPosition(Vector pos, char grid[], int grid_size_x, int grid_size_y);

    void setObjectAtPosition(GridObjects obj, Vector pos, char grid[], int grid_size_x, int grid_size_y);
#endif