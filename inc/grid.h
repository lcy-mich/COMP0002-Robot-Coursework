#ifndef GRID_H
    #define GRID_H
    
    #include <vectors.h>

    typedef enum GridObjects {
        AIR, WALL, MARKER
    } GridObjects;


    GridObjects getObjectAtPosition(Vector pos, int grid[], Vector grid_size);
    int setObjectAtPosition(GridObjects obj, Vector pos, int grid[], Vector grid_size);

    void clearGrid(int* grid, Vector grid_size);
#endif 