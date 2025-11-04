#include "../inc/grid.h"
#include "../inc/vectors.h"

int getIndexFromVector(Vector pos, int grid_size_x, int grid_size_y) {
    if (((pos.x < grid_size_x) && (pos.x >= 0 )) && ((pos.y < grid_size_y) && (pos.y >= 0 ))) {
        return pos.x + pos.y*grid_size_y;
    }
    printf("Error: Invalid position (%f, %f)", pos.x, pos.y);
    return -1;
}

GridObjects getObjectAtPosition(Vector pos, char grid[], int grid_size_x, int grid_size_y) {
    return grid[getIndexFromVector(pos, grid_size_x, grid_size_y)];
}

void setObjectAtPosition(GridObjects obj, Vector pos, char grid[], int grid_size_x, int grid_size_y) {
    grid[getIndexFromVector(pos, grid_size_x, grid_size_y)] = obj;
}