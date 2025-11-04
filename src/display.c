#include <display.h>

void _drawCheese(Vector pos, float scale, int grid_side_length) {
    fillPolygon(
        3, 
        (int[3]){
            pos.x*grid_side_length + (1-scale)*grid_side_length/2, 
            (1 + pos.x)*grid_side_length - 1 - (1-scale)*grid_side_length/2, 
            (1 + pos.x)*grid_side_length - 1 - (1-scale)*grid_side_length/2
        },
        (int[3]){
            pos.y*grid_side_length + grid_side_length/2, 
            pos.y*grid_side_length + (1-scale)*grid_side_length/2, 
            (1 + pos.y)*grid_side_length - 1 - (1-scale)*grid_side_length/2
        }
    );
}

void _drawMouseBody(Vector pos, Directions dir, float scale, int grid_side_length) {
    int is_vertical = dir % 2; // returns 1 if enum is in a vertical direction
    
    //swap x and y to turn verticals
    int x = (
        is_vertical ?
            (0.25 + pos.x)*grid_side_length - 1 + (grid_side_length*(1-scale))/2 :
            pos.x*grid_side_length + (grid_side_length*(1-scale))/2
    );
    int y = (
        is_vertical ?
            pos.y*grid_side_length + (grid_side_length*(1-scale))/2 :
            (0.25 + pos.y)*grid_side_length - 1 + (grid_side_length*(1-scale))/2
    );

    //swap width and height to turn vertical
    int width = (
        is_vertical ? 
            scale*grid_side_length/2 : 
            scale*grid_side_length - 2
    );
    int height = (
        is_vertical ? 
            scale*grid_side_length - 2 :
            scale*grid_side_length/2
    );


    fillOval(
        x, 
        y, 
        width, height 
    );
}

void _drawMouseEars(Vector pos, Directions dir, float scale, int grid_side_length) {
    int is_vertical = dir % 2;
    
    //swap x and y if vertical
    int x = (is_vertical ? pos.y : pos.x)*grid_side_length + (1.05 - scale)*grid_side_length/2  + grid_side_length*(dir - 1*is_vertical)/4; //last term makes the ears shift to the correct side
    int y = (is_vertical ? pos.x : pos.y)*grid_side_length + (1.15 - scale)*grid_side_length/2;

    int side_size = grid_side_length*scale/3;

    fillOval(
        (is_vertical ? y : x), 
        (is_vertical ? x : y),
        side_size, side_size
    );
    fillOval(
        (is_vertical ?  -y  + (2*pos.x + 1)*grid_side_length - 1 - grid_side_length*scale/3 : x),
        (is_vertical ? x : -y  + (2*pos.y + 1)*grid_side_length - 1 - grid_side_length*scale/3),
        side_size, side_size
    );
}

void drawGrid(int grid_side_length, Vector grid_size) {

    for (int x = grid_side_length - 1; x < grid_side_length*grid_size.x - 1; x+=grid_side_length) {
        drawLine(x, 0, x, grid_side_length*grid_size.y - 1);
    }
    for (int y = grid_side_length - 1; y < grid_side_length*grid_size.y - 1; y+=grid_side_length) {
        drawLine(0, y, grid_side_length*grid_size.x - 1, y);
    }

}

void drawMarker(Vector pos, float scale, int grid_side_length){

    setColour(orange);

    _drawCheese(pos, scale, grid_side_length);

    setColour(black);

}

void drawRobot(Vector pos, Directions dir, float scale, int grid_side_length) {
    //draw mouse


    setColour(gray);
    _drawMouseBody(pos, dir, scale, grid_side_length);
    setColour(pink);
    _drawMouseEars(pos, dir, scale, grid_side_length);
    setColour(black);
}

void initialise(int grid_side_length, Vector grid_size) {

    setWindowSize(grid_side_length*grid_size.x, grid_side_length*grid_size.y);

    background();
    drawGrid(grid_side_length, grid_size);
    foreground();
}