#ifndef GRID_H
    #define GRID_H

    #include "vectors.h"

    typedef enum grid_objects {
        AIR, WALL, MARKER
    } GridObjects;


    int getIndexFromVector(Vector, int grid_size_y);

#endif