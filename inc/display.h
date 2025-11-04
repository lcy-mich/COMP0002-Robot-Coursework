#ifndef DISPLAY_H
    #define DISPLAY_H

    #include <robot.h>
    #include <graphics.h>
    
    void initialise(int grid_side_length, Vector grid_side);
    
    void drawMarker(Vector pos, int grid_side_length);
    void drawRobot(Vector pos, Directions dir, int grid_side_length);
    void drawWall(Vector pos, int grid_side_length);
#endif