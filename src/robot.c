<<<<<<< HEAD
#include <robot.h>
#include <grid.h>
=======
#include "include/robot.h"
#include "include/grid.h"
>>>>>>> 6487e565e942cdaafad3500309c14dc63cef0d30

//corresponds to the directions enum indices in robot.h
const Vector DIR_VECTORS[4] = {

    {-1, 0}, {0, -1}, {1, 0}, {0, 1} //LEFT, UP, RIGHT, DOWN

}; 

<<<<<<< HEAD
int canMoveForward(Vector pos_after_movement, char grid[], Vector grid_size) {

    if (getObjectAtPosition(pos_after_movement, grid, grid_size) == AIR) {
=======
int canMoveForward(Vector pos_after_movement, char grid[], int grid_size_x, int grid_size_y) {
    if (((pos_after_movement.x < grid_size_x) || (pos_after_movement.x >= 0 )) && 
        ((pos_after_movement.y < grid_size_y) || (pos_after_movement.y >= 0 )) &&
        (grid[getIndexFromVector(pos_after_movement, grid_size_y)] == AIR)) {
>>>>>>> 6487e565e942cdaafad3500309c14dc63cef0d30
        return 1;
    }

    return 0;

}

void forward(Robot* robot, char grid[], Vector grid_size) {

    Vector pos_after_movement = add(robot->pos, DIR_VECTORS[robot->dir]);
    
<<<<<<< HEAD
    if (canMoveForward(pos_after_movement, grid, grid_size)) { 
        robot->pos = pos_after_movement;
    }

=======
    if (canMoveForward(pos_after_movement, grid, grid_size_x, grid_size_y)) { 
        robot->pos = pos_after_movement;
    }
>>>>>>> 6487e565e942cdaafad3500309c14dc63cef0d30
}

//goes to the left element of directions enum and loops back using modulo
void left(Robot* robot) {

    robot->dir = (robot->dir --) % 4;

} 

//goes to the right element of directions enum and loops back using modulo
void right(Robot* robot) {

    robot->dir = (robot->dir ++) % 4;

}

<<<<<<< HEAD
int atMarker(Vector pos, char grid[], Vector grid_size) {

    return getObjectAtPosition(pos, grid, grid_size) == MARKER;

}

void dropMarker(Robot* robot, char grid[], Vector grid_size) {

    if (setObjectAtPosition(MARKER, robot->pos, grid, grid_size)) {
        robot->held_markers--;
    }

}

int markerCount(Robot* robot) {

    return robot->held_markers;
    
=======
int atMarker(Vector pos, char grid[], int grid_size_y) {
    return (grid[getIndexFromVector(pos, grid_size_y)] == MARKER);
>>>>>>> 6487e565e942cdaafad3500309c14dc63cef0d30
}