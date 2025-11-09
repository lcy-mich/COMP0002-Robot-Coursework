#include <maploader.h>

#include <graphics.h>
#include <string.h>
#include <stdio.h>

int getObjectFromChar(char a) {

    switch (a) {
        case '.':
            return AIR;
        case '#':
            return WALL;
        case '$':
            return MARKER;
        default:
            return -1;
    }

}

int safeGetLine(char* buffer, int buffer_size, FILE *file_pointer) {
    if (fgets(buffer, buffer_size, file_pointer) == NULL) {
        fclose(file_pointer);
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
        return 0;
    }
    initial_grid_size.x = atoi(buffer);

    if (!safeGetLine(buffer, BUFFER_SIZE, file_pointer)) {
        return 0;
    }
    initial_grid_size.y = atoi(buffer);
    
    memcpy(grid_size, &initial_grid_size, sizeof(initial_grid_size));

    //get grid_side_length
    if (!safeGetLine(buffer, BUFFER_SIZE, file_pointer)) {
        return 0;
    }
    int side_length = atoi(buffer);
    memcpy(grid_side_length, &side_length, sizeof(side_length));

    //get total_markers
    if (!safeGetLine(buffer, BUFFER_SIZE, file_pointer)) {
        return 0;
    }
    int markers = atoi(buffer);
    memcpy(total_markers, &markers, sizeof(markers));

    fclose(file_pointer);
    return 1;
}

int readMap(Robot* robot, int* grid, Vector grid_size, Vector* marker_pos, char* file_name) {
    //check if file can be accessed
    FILE *file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL) {
        message("file pointer null");
        return 0;
    }

    char buffer[BUFFER_SIZE];
    int marker_pos_index = 0;

    for (int i = 0; i < 4; i++) {
        fgets(buffer, BUFFER_SIZE, file_pointer);
    }

    for (int y = 0; y < grid_size.y; y++) {
        if (fgets(buffer, BUFFER_SIZE, file_pointer) == NULL) {
            fclose(file_pointer);
            message("empty file");
            break;
        }
        
        for (int x = 0; x < grid_size.x; x++) {
            int obj = getObjectFromChar(buffer[x]);
            if (obj == MARKER) {
                marker_pos[marker_pos_index] = (Vector){x,y};
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

                memcpy(robot, &initial_robot, sizeof(initial_robot));
                
                obj = AIR;
            }
            
            setObjectAtPosition(obj, (Vector){x,y}, grid, grid_size);
        }
    }
    fclose(file_pointer);
    return 1;
} 