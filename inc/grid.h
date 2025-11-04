#ifndef GRID_H
    #define GRID_H

    #include <vectors.h>

    typedef enum {
        AIR, WALL, MARKER
    } GridObjects;


    GridObjects getObjectAtPosition(Vector pos, char grid[], Vector grid_size);
    int setObjectAtPosition(GridObjects obj, Vector pos, char grid[], Vector grid_size);

#endif 