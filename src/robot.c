#include <robot.h>
#include <grid.h>

//corresponds to the directions enum indices in robot.h
const Vector DIR_VECTORS[4] = {

    {-1, 0}, {0, -1}, {1, 0}, {0, 1} //LEFT, UP, RIGHT, DOWN

}; 

int canMoveForward(Vector pos_after_movement, char grid[], Vector grid_size) {

    if (getObjectAtPosition(pos_after_movement, grid, grid_size) == AIR) {
        return 1;
    }

    return 0;

}

void forward(Robot* robot, char grid[], Vector grid_size) {

    Vector pos_after_movement = add(robot->pos, DIR_VECTORS[robot->dir]);
    
    if (canMoveForward(pos_after_movement, grid, grid_size)) { 
        robot->pos = pos_after_movement;
    }

}

//goes to the left element of directions enum and loops back using modulo
void left(Robot* robot) {

    robot->dir = (robot->dir --) % 4;

} 

//goes to the right element of directions enum and loops back using modulo
void right(Robot* robot) {

    robot->dir = (robot->dir ++) % 4;

}

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
    
}