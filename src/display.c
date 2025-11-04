#include <display.h>

//hard-coded cheese body
void _drawCheese(Vector pos, int grid_side_length) {
    fillPolygon(
        3, 
        (int[3]){
            pos.x*grid_side_length + .15*grid_side_length/2, 
            (1 + pos.x)*grid_side_length - 1 - .15*grid_side_length/2, 
            (1 + pos.x)*grid_side_length - 1 - .15*grid_side_length/2
        },
        (int[3]){
            pos.y*grid_side_length + grid_side_length/2, 
            pos.y*grid_side_length + .15*grid_side_length/2, 
            (1 + pos.y)*grid_side_length - 1 - .15*grid_side_length/2
        }
    );
}

//hard-coded mouse body
void _drawMouseBody(Vector pos, Directions dir, int grid_side_length) {
    int is_vertical = dir % 2; // returns 1 if enum is in a vertical direction
    
    //swap x and y to turn verticals
    int x = (
        is_vertical ?
            (0.25 + pos.x)*grid_side_length - 1 :
            pos.x*grid_side_length
    );
    int y = (
        is_vertical ?
            pos.y*grid_side_length :
            (0.25 + pos.y)*grid_side_length - 1
    );

    //swap width and height to turn vertical
    int width = (
        is_vertical ? 
            grid_side_length/2 : 
            grid_side_length - 2
    );
    int height = (
        is_vertical ? 
            grid_side_length - 2 :
            grid_side_length/2
    );


    fillOval(
        x, 
        y, 
        width, height 
    );
}

//hard-coded mouse ears
void _drawMouseEars(Vector pos, Directions dir, int grid_side_length) {
    int is_vertical = dir % 2;
    
    //swap x and y if vertical
    int x = (is_vertical ? pos.y : pos.x)*grid_side_length + .05*grid_side_length/2  + grid_side_length*(dir - 1*is_vertical)/4; //last term makes the ears shift to the correct side
    int y = (is_vertical ? pos.x : pos.y)*grid_side_length + .15*grid_side_length/2;

    int side_size = grid_side_length/3;

    fillOval(
        (is_vertical ? y : x), 
        (is_vertical ? x : y),
        side_size, side_size
    );

    fillOval(
        (is_vertical ?  -y  + (2*pos.x + 1)*grid_side_length - 1.15*side_size : x),
        (is_vertical ? x : -y  + (2*pos.y + 1)*grid_side_length - 1.15*side_size),
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

void drawMarker(Vector pos, int grid_side_length){

    setColour(orange);
    _drawCheese(pos, grid_side_length);

    setColour(black);

}

void drawRobot(Vector pos, Directions dir, int grid_side_length) {
    
    setColour(gray);
    _drawMouseBody(pos, dir, grid_side_length);

    setColour(pink);
    _drawMouseEars(pos, dir, grid_side_length);

    setColour(black);

}

void initialise(int grid_side_length, Vector grid_size) {

    setWindowSize(grid_side_length*grid_size.x, grid_side_length*grid_size.y);

    background();
    drawGrid(grid_side_length, grid_size);

    foreground();

}