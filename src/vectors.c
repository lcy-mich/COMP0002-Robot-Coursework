#include <vectors.h>
#include <math.h>

// corresponds to the directions enum indices in vectors.h
const Vector DIR_VECTORS[DIR_AMOUNT] = {

    {-1, 0}, {0, -1}, {1, 0}, {0, 1} // LEFT, UP, RIGHT, DOWN

};

Vector getVectorFromDirection(Directions dir) {

    return DIR_VECTORS[dir];

}

Directions getDirectionFromChar(char a) {

    switch (a) {
        case '^':
            return UP;
        case '>':
            return RIGHT;
        case '<':
            return LEFT;
        case 'v':
            return DOWN;
        default:
            return -1;
    }

}

Vector add(Vector a, Vector b) {

    return (Vector){a.x + b.x, a.y + b.y};

}

Vector sub(Vector a, Vector b) {

    return add(a, neg(b));

}

Vector neg(Vector a) {

    return (Vector){- a.x, - a.y};

}

float distance(Vector a, Vector b) {
    Vector diff = sub(a,b);
    Vector square = {diff.x * diff.x, diff.y * diff.y};
    return sqrtf((float)(square.x + square.y));
}

int equals(Vector a, Vector b) {
    return (a.x == b.x && a.y == b.y);
}