#include <display.h>

int main() {

    int grid_side_length = 50;
    Vector grid_size = {20, 20};
    initialise(grid_side_length, grid_size);
    drawMarker((Vector){2, 4}, grid_side_length);
    drawRobot((Vector){6, 10}, LEFT, grid_side_length);
    drawWall((Vector){3,3}, grid_side_length);
    return 0;

}