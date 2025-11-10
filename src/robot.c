#include <robot.h>

int canMoveForward(Robot robot, int grid[], Vector grid_size) {

    Vector pos_after_movement = add(robot.pos, getVectorFromDirection(robot.dir));

    if ((getObjectAtPosition(pos_after_movement, grid, grid_size) != WALL) &&
        (pos_after_movement.x >= 0 && pos_after_movement.x < grid_size.x) &&
        (pos_after_movement.y >= 0 && pos_after_movement.y < grid_size.y)) {

        return 1;
    }

    return 0;

}

void forward(Robot* robot, int grid[], Vector grid_size) {
 
    if (canMoveForward(*robot, grid, grid_size)) { 
        robot->pos = add(robot->pos, getVectorFromDirection(robot->dir));
    }

}

//goes to the left element of directions enum and loops back using modulo
void left(Robot* robot) {

    robot->dir = (robot->dir + 3) % 4;

} 

//goes to the right element of directions enum and loops back using modulo
void right(Robot* robot) {

    robot->dir = (robot->dir + 1) % 4;

}

int atMarker(Robot robot, int grid[], Vector grid_size) {

    return getObjectAtPosition(robot.pos, grid, grid_size) == MARKER;

}

void pickUpMarker(Robot* robot, int grid[], Vector grid_size) {
    
    if (atMarker(*robot, grid, grid_size)) {
        setObjectAtPosition(AIR, robot->pos, grid, grid_size);
        robot->held_markers++;
    }
    
}

void dropMarker(Robot* robot, int grid[], Vector grid_size) {

    if (!atMarker(*robot, grid, grid_size) && setObjectAtPosition(MARKER, robot->pos, grid, grid_size)) {
        robot->held_markers--;
    }

}

int markerCount(Robot* robot) {

    return robot->held_markers;
    
}
