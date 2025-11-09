#define DEBUG_MODE

#include <display.h>
#include <robot.h>
#include <astar.h>

#include <maploader.h>

Vector getClosestMarkerPosition(Vector pos, Vector* marker_pos, int total_markers){

    Vector closest;
    int least_dist = INT_MAX;
    for (int i = 0; i < total_markers; i++) {
        int dist = distance(marker_pos[i], pos);
        if (dist <= least_dist) {
            closest = marker_pos[i];
            least_dist = dist;
        }
    }
    return closest;

}

void update(Robot* robot, int table_size, int grid[], Vector grid_size, Vector* marker_pos, int* total_markers, int* finished, LinkedList** path[]){

    if (*total_markers > 0) {
        if (equals(robot->current_target, NULL_VECTOR) || getObjectAtPosition(robot->current_target, grid, grid_size) != MARKER) {
            //message("GOOOOOOOODDDDDDDDDDDDDD DAAAAAAAAAAAAAAAAAAAAAAAAAYUUUUUUUUUUMN");
            robot->current_target = getClosestMarkerPosition(robot->pos, marker_pos, *total_markers);
            *path = pathfind(robot, robot->current_target, table_size, grid, grid_size);
        }

        followPath(robot, *path, table_size, grid, grid_size);

        if (atMarker(*robot, grid, grid_size)) {
            pickUpMarker(robot, grid, grid_size);
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
        *finished = 0;
    }

}

int main(int argc, char** argv) {
    
    int total_markers = 0;
    Vector* marker_pos;

    int grid_side_length = 40;
    Vector grid_size = {10, 10};

    Robot robot;
    robot.current_target = NULL_VECTOR;
    robot.pos = (Vector){grid_size.x/2, grid_size.y/2};
    robot.dir = UP;
    robot.held_markers = 0;

    LinkedList** path;

    //int generate_map = 1;

    if (argc == 2 || argc == 1) {
        if (argc == 2 && !getMetadata(&grid_size, &grid_side_length, &total_markers, argv[1])) {
            message("metadata failed");
            return 1;
        }
        //generate_map = 0;
    }
    int grid[grid_size.x*grid_size.y];
    marker_pos = malloc(sizeof(Vector)*total_markers);
    clearGrid(grid, grid_size);

    switch (argc) {
        case 2:
            if (!readMap(&robot, grid, grid_size, marker_pos, argv[1])) {
                message("map read failed");
                return 2;
            }
            break;
        case 4:
            robot.pos = (Vector){atoi(argv[1]), atoi(argv[2])};
            robot.dir = getDirectionFromString(argv[3]);
    }
    
    renderGrid(grid, grid_side_length, grid_size);

    int finished = 0;
    while (!finished) {
        clear();
        update(&robot, grid_size.x*grid_size.y, grid, grid_size, marker_pos, &total_markers, &finished, &path);
        renderObjects(grid, grid_side_length, grid_size);
        renderRobot(robot, grid_side_length);
        sleep(100);
    }
    free(marker_pos);
    marker_pos = NULL;
    return 0;
}