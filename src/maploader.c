#include <maploader.h>

#include <graphics.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define AIR_CHAR '.'
#define WALL_CHAR '#'
#define MARKER_CHAR '$'

#define MAX_RADIUS (smaller_side / 2)
#define MIN_RADIUS (smaller_side / 10)

#define MAX_GRID_SIZE_X 50
#define MIN_GRID_SIZE_X 20

#define MAX_GRID_SIZE_Y 50
#define MIN_GRID_SIZE_Y 20

#define MIN_MARKERS 5

#define SEED_DIVISOR 10

#define MAX_WALL_SIZE 5
#define MIN_WALL_SIZE 3


int getObjectFromChar(char a) {

    switch (a) {
        case AIR_CHAR:
            return AIR;
        case WALL_CHAR:
            return WALL;
        case MARKER_CHAR:
            return MARKER;
        default:
            return -1;
    }

}

int safeGetLine(char* buffer, int buffer_size, FILE* file_pointer) {
    if (fgets(buffer, buffer_size, file_pointer) == NULL) {
        return 0;
    }
    return 1;
}

int getMetadata(Vector* grid_size, int* grid_side_length, int* total_markers, char* file_name) {
    //check if file can be accessed
    FILE *file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL) {
        return 0;
    }

    char buffer[BUFFER_SIZE];

    //get metadata

    //get grid_size
    Vector initial_grid_size;

    if (!safeGetLine(buffer, BUFFER_SIZE, file_pointer)) {
        message("failed to read x size");
        fclose(file_pointer);
        file_pointer = NULL;
        return 0;
    }
    initial_grid_size.x = atoi(buffer);

    if (!safeGetLine(buffer, BUFFER_SIZE, file_pointer)) {
        message("failed to read y size");
        fclose(file_pointer);
        file_pointer = NULL;
        return 0;
    }
    initial_grid_size.y = atoi(buffer);

    *grid_size = initial_grid_size;

    //get grid_side_length
    if (!safeGetLine(buffer, BUFFER_SIZE, file_pointer)) {
        message("failed to read grid side length");
        fclose(file_pointer);
        file_pointer = NULL;
        return 0;
    }
    int side_length = atoi(buffer);
    *grid_side_length = side_length;

    //get total_markers
    if (!safeGetLine(buffer, BUFFER_SIZE, file_pointer)) {
        message("failed to read total markers");
        fclose(file_pointer);
        file_pointer = NULL;
        return 0;
    }
    *total_markers = atoi(buffer);

    fclose(file_pointer);
    return 1;
}

int readMap(Robot* robot, int* grid[], Vector grid_size, Vector* marker_pos[], int total_markers, char* file_name) {
    *grid = malloc(sizeof(int) *grid_size.x*grid_size.y);
    *marker_pos = malloc(sizeof(Vector)*total_markers);

    clearGrid(*grid, grid_size);

    //check if file can be accessed
    FILE *file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL) {
        message("file pointer null");
        return 0;
    }

    char buffer[BUFFER_SIZE];
    int marker_pos_index = 0;

    for (int i = 0; i < 4; i++) {
        if (fgets(buffer, BUFFER_SIZE, file_pointer) == NULL) {
            fclose(file_pointer);
            message("unexpected eof");
            return 0;
        }
    }

    for (int y = 0; y < grid_size.y; y++) {
        if (fgets(buffer, BUFFER_SIZE, file_pointer) == NULL) {
            fclose(file_pointer);
            message("unexpected eof");
            return 0;
        }
        
        for (int x = 0; x < grid_size.x; x++) {
            int obj = getObjectFromChar(buffer[x]);
            if (obj == MARKER && marker_pos_index < total_markers) {
                (*marker_pos)[marker_pos_index] = (Vector){x,y};
                marker_pos_index++;
            }

            if (obj == -1) {
                obj = getDirectionFromChar(buffer[x]);

                if (obj == -1) {
                    message("invalid character read");
                    continue;
                }
                
                Robot initial_robot;

                initial_robot.dir = obj;
                initial_robot.pos = (Vector){x, y};
                initial_robot.held_markers = 0;

                *robot = initial_robot;
                
                obj = AIR;
            }
            
            setObjectAtPosition(obj, (Vector){x,y}, *grid, grid_size);
        }
    }
    fclose(file_pointer);
    if (marker_pos_index != total_markers) {
        message("marker count mismatch");
        return 0;
    }
    return 1;
} 


void drawCircleBounds(int radius, int grid[], Vector grid_size, int* remaining_space) {

    for (int y = 0; y < grid_size.y; y++) {

        for (int x = 0; x < grid_size.x; x++) {

            Vector centre = {grid_size.x / 2, grid_size.y / 2};
            Vector pos = {x, y};

            if (distance(centre, pos) > radius) {
                setObjectAtPosition(WALL, pos, grid, grid_size);
                (*remaining_space)--;
            }

        }
    }
}

void generateMap(Robot* robot, int* grid[], Vector* grid_size, int* grid_side_length, Vector* marker_pos[], int* total_markers) {
    srand((unsigned)time(NULL));
    grid_size->x = (rand() % (MAX_GRID_SIZE_X - MIN_GRID_SIZE_X)) + MIN_GRID_SIZE_X;
    grid_size->y = (rand() % (MAX_GRID_SIZE_Y - MIN_GRID_SIZE_Y)) + MIN_GRID_SIZE_Y;

    int remaining_space = grid_size->x * grid_size->y;
    *grid = malloc(sizeof(int) * remaining_space);
    
    clearGrid(*grid, *grid_size);

    int smaller_side = grid_size->x < grid_size->y ? grid_size->x : grid_size->y;
    *grid_side_length = smaller_side / 2;

    drawCircleBounds((rand() % (MAX_RADIUS - MIN_RADIUS)) + MIN_RADIUS , *grid, *grid_size, &remaining_space);

    // generate walls
    
    // plant seeds
    int seed_amount = remaining_space ? rand() % (remaining_space/ SEED_DIVISOR) : 0;
    Vector* seeds;
    if (seed_amount > 0) {
        seeds = malloc(sizeof(Vector) * seed_amount);
    } else {
        seeds = NULL;
    }  
    for (int i = 0; i < seed_amount; i++) {
        Vector pos;
        do {
            pos = (Vector){
                rand() % grid_size->x,
                rand() % grid_size->y
            };
        } while (getObjectAtPosition(pos, *grid, *grid_size) != AIR);

        setObjectAtPosition(WALL, pos, *grid, *grid_size);
        seeds[i] = pos;
        remaining_space--;
    }

    // grow walls from seeds
    for (int seed_index = 0; seed_index < seed_amount; seed_index++) {
        Vector seed_pos = seeds[seed_index];
        int wall_growth_length = rand() % (MAX_WALL_SIZE - MIN_WALL_SIZE) + MIN_WALL_SIZE;

        // int growth_step = 0;
        int growth_step = 0;
        while (growth_step < wall_growth_length) {
            Vector dir = getVectorFromDirection(rand() % DIR_AMOUNT);
            Vector new_pos = add(seed_pos, dir);

            if (getObjectAtPosition(new_pos, *grid, *grid_size) == AIR) {
                setObjectAtPosition(WALL, new_pos, *grid, *grid_size);
                remaining_space--;
                
                seed_pos = new_pos;
                
            }
            growth_step++;
        }
    }
    
    // generate marker_pos and place markers
    *total_markers = rand() % abs(remaining_space/10 - MIN_MARKERS) + MIN_MARKERS ;
    *marker_pos = malloc(sizeof(Vector) * (*total_markers));

    for (int i = 0; i < *total_markers; i++) {
        Vector pos;
        do {
            pos = (Vector){
                rand() % grid_size->x,
                rand() % grid_size->y
            };
        } while (getObjectAtPosition(pos, *grid, *grid_size) != AIR);

        (*marker_pos)[i] = pos;
        setObjectAtPosition(MARKER, pos, *grid, *grid_size);
    }

    // place robot with random pos and dir
    Vector robot_pos;
    do {
        robot_pos = (Vector){
            rand() % grid_size->x,
            rand() % grid_size->y
        };
    } while (getObjectAtPosition(robot_pos, *grid, *grid_size) != AIR);

    robot->pos = robot_pos;
    robot->dir = rand() % 4;
}
