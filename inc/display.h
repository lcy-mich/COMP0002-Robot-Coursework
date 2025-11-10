#ifndef DISPLAY_H
    #define DISPLAY_H

    #include <robot.h>
    #include <graphics.h>

    void drawGrid(int grid_side_length, Vector grid_size);
    
    void renderGrid(int grid[], int grid_side_length, Vector grid_size);

    void renderObjects(int grid[], int grid_side_length, Vector grid_size);

    void renderRobot(Robot robot, int grid_side_length);

    #ifdef DEBUG_MODE
        void drawMarker(Vector pos, int grid_side_length);
        void drawRobot(Vector pos, Directions dir, int grid_side_length);
        void drawWall(Vector pos, int grid_side_length);
    #endif

#endif