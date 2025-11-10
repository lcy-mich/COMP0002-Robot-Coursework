#include <stdio.h>
#include <stdlib.h>

#include <display.h>
#include <robot.h>
#include <astar.h>

#include <maploader.h>

#define FALLBACK_GRID_SIDE_LENGTH 40
#define FALLBACK_GRID_SIZE (Vector){10, 10}
#define FALLBACK_ROBOT_START_POS (Vector){FALLBACK_GRID_SIZE.x/2, FALLBACK_GRID_SIZE.y/2}
#define FALLBACK_ROBOT_START_DIR UP


void update(Robot* robot, int table_size, int grid[], Vector grid_size, Vector* marker_pos, int* total_markers, int* finished, LinkedList** path[]){

    if (*total_markers > 0) {

        if (equals(robot->current_target, NULL_VECTOR) || getObjectAtPosition(robot->current_target, grid, grid_size) != MARKER) {
            
            robot->current_target = getClosestMarkerPosition(robot->pos, marker_pos, *total_markers);
            
            *path = pathfind(robot, robot->current_target, table_size, grid, grid_size);
        
        }

        int moved = followPath(robot, *path, table_size, grid, grid_size);

        if (!moved || atMarker(*robot, grid, grid_size)) {

            robot->current_target = NULL_VECTOR;

            if (atMarker(*robot, grid, grid_size)) {
                pickUpMarker(robot, grid, grid_size);
            }

            freePath(*path, table_size);
            *path = NULL;

            for (int marker_index = 0; marker_index < *total_markers; marker_index++) {

                if (equals(marker_pos[marker_index], robot->pos)) {

                    marker_pos[marker_index] = marker_pos[*total_markers-1];

                    break;

                }

            }

            (*total_markers)--;

        }

    }
    else {

        *finished = 1;

    }

}

int main(int argc, char** argv) {
    
    int total_markers = 0;
    Vector* marker_pos = NULL;

    int* grid = NULL;
    int grid_side_length = FALLBACK_GRID_SIDE_LENGTH;
    Vector grid_size = FALLBACK_GRID_SIZE;

    Robot robot;
    robot.current_target = NULL_VECTOR;
    robot.pos = FALLBACK_ROBOT_START_POS;
    robot.dir = FALLBACK_ROBOT_START_DIR;
    robot.held_markers = 0;

    LinkedList** path = NULL;

    switch (argc) {

        case 2:

            if (!getMetadata(&grid_size, &grid_side_length, &total_markers, argv[1])) {
                message("metadata read error");
                return EXIT_FAILURE;
            }

            if (!readMap(&robot, &grid, grid_size, &marker_pos, total_markers, argv[1])) {
                message("map read error");
                return EXIT_FAILURE;
            }

            break;

        default:
        
            generateMap(&robot, &grid, &grid_size, &grid_side_length, &marker_pos, &total_markers);

            break;

    }
    
    renderGrid(grid, grid_side_length, grid_size);

    int finished = 0;

    while (!finished) {

        clear();
        
        update(&robot, grid_size.x*grid_size.y, grid, grid_size, marker_pos, &total_markers, &finished, &path);
        
        renderObjects(grid, grid_side_length, grid_size);
        renderRobot(robot, grid_side_length);

        sleep(150);

    }

    free(marker_pos);
    marker_pos = NULL;

    free(grid);
    grid = NULL;

    return EXIT_SUCCESS;
}