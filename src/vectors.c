#include <vectors.h>
#include <math.h>

//corresponds to the directions enum indices in vectors.h
const Vector DIR_VECTORS[4] = {

    {-1, 0}, {0, -1}, {1, 0}, {0, 1} //LEFT, UP, RIGHT, DOWN

};

Vector getVectorFromDirection(Directions dir) {
    return DIR_VECTORS[dir];
}

Directions getDirectionFromString(char* string) {
    if (string[0] == 'l' || string[0] == 'L') {
        return LEFT;
    }
    else if (string[0] == 'r' || string[0] == 'R') {
        return RIGHT;
    }
    else if (string[0] == 'u' || string[0] == 'U') {
        return UP;
    }
    else if (string[0] == 'd' || string[0] == 'D') {
        return DOWN;
    }
    else {
        return -1;
    }
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

Vector scale(float factor, Vector a) {

    return (Vector){factor * a.x, factor * a.y};
    
}

float distance(Vector a, Vector b) {
    Vector diff = sub(a,b);
    Vector square = {diff.x * diff.x, diff.y * diff.y};
    return sqrtf((float)(square.x + square.y));
}

int equals(Vector a, Vector b) {
    return (a.x == b.x && a.y == b.y);
}