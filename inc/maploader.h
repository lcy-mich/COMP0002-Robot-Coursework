#ifndef MAPLOADER_H
    #define MAPLOADER_H

    #include <grid.h>
    #include <robot.h>

    #define BUFFER_SIZE 512

    int getMetadata(Vector* grid_size, int* grid_side_length, int* total_markers, char* file_name);
    int readMap(Robot* robot, int* grid[], Vector grid_size, Vector* marker_pos[], int total_markers, char* file_name);

    void generateMap(Robot* robot, int* grid[], Vector* grid_size, int* grid_side_length, Vector* marker_pos[], int* total_markers);

#endif