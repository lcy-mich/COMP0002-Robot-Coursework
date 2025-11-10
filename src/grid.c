#include <grid.h>

int getIndexFromVector(Vector pos, Vector grid_size) {

    if (((pos.x < grid_size.x) && (pos.x >= 0 )) && 
        ((pos.y < grid_size.y) && (pos.y >= 0 ))) {
        
        return pos.x + pos.y*grid_size.x;

    }

    return -1;

}

GridObjects getObjectAtPosition(Vector pos, int grid[], Vector grid_size) {

    int index = getIndexFromVector(pos, grid_size);

    if (index < 0) {

        return WALL;

    }

    return grid[index];

}

// returns true if object has been set
int setObjectAtPosition(GridObjects obj, Vector pos, int grid[], Vector grid_size) {
    
    int index = getIndexFromVector(pos, grid_size);

    if (index < 0) {

        return 0;

    }
    
    if (getObjectAtPosition(pos, grid, grid_size) != obj) {

        grid[index] = obj;

        return 1;

    }

    return 0; 

}

void clearGrid(int* grid, Vector grid_size) {

    for (int y = 0; y < grid_size.y; y++) {

        for (int x = 0; x < grid_size.x; x++) {

            setObjectAtPosition(AIR, (Vector){x, y}, grid, grid_size);

        }

    }

}