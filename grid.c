#include "grid.h"
#include "vectors.h"

int getIndexFromVector(Vector pos, int grid_size_y) {
    return pos.x + pos.y*grid_size_y;
}