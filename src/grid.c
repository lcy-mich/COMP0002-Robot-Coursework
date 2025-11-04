#include <grid.h>

int getIndexFromVector(Vector pos, Vector grid_size) {

    if (((pos.x < grid_size.x) && (pos.x >= 0 )) && ((pos.y < grid_size.y) && (pos.y >= 0 ))) {
        return pos.x + pos.y*grid_size.y;
    }

    printf("Error: Invalid position (%f, %f)", pos.x, pos.y);
    
    return -1;

}

GridObjects getObjectAtPosition(Vector pos, char grid[], Vector grid_size) {

    return grid[getIndexFromVector(pos, grid_size)];

}

// returns true if object has been set
int setObjectAtPosition(GridObjects obj, Vector pos, char grid[], Vector grid_size) {
    
    if (getObjectAtPosition(pos, grid, grid_size) != obj) {
        grid[getIndexFromVector(pos, grid_size)] = obj;
        return 1;
    }

    return 0; 

}