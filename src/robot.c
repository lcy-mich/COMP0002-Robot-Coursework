#include "include/robot.h"

//corresponds to the directions enum indices in robot.h
const Vector DIR_VECTORS[] = {
    {-1, 0}, {0, -1}, {1, 0}, {0, 1} //LEFT, UP, RIGHT, DOWN
}; 

int canMoveForward(Vector pos_after_movement, char grid[], int grid_size_x, int grid_size_y) {
    if (
        ((pos_after_movement.x < grid_size_x) || (pos_after_movement.x >= 0 )) && 
        ((pos_after_movement.y < grid_size_y) || (pos_after_movement.y >= 0 )) &&
        (grid[getIndexFromVector(pos_after_movement, grid_size_y)])) {
        return 1;
    }
    return 0;
}

void forward(Robot* robot, char grid[], int grid_size_x, int grid_size_y) {
    Vector pos_after_movement = add(robot->pos, DIR_VECTORS[robot->dir]);
    
    //if (canMoveForward(pos_after_movement, grid, grid_size_x, grid_size_y)) { 
        robot->pos = pos_after_movement;
    //}
}

//goes to the left element of directions enum and loops back using modulo
void left(Robot* robot) {
    robot->dir = (robot->dir - 1) % 4;
} 

//goes to the right element of directions enum and loops back using modulo
void right(Robot* robot) {
    robot->dir = (robot->dir + 1) % 4;
}

void atMarker(Vector position) {
    return ()
}