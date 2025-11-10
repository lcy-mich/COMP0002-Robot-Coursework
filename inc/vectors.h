#ifndef VECTORS_H
    #define VECTORS_H

    #include <limits.h>
    #define NULL_VECTOR (Vector){-INT_MAX, -INT_MAX}
    #define DIR_AMOUNT 4

    typedef struct {
        int x;
        int y;
    } Vector;

    typedef enum Directions {
        LEFT, UP, RIGHT, DOWN
    } Directions;

    extern const Vector DIR_VECTORS[DIR_AMOUNT];

    Vector getVectorFromDirection(Directions dir);

    Directions getDirectionFromString(char*);

    Directions getDirectionFromChar(char);

    Vector add(Vector, Vector);

    Vector sub(Vector, Vector);

    Vector neg(Vector);

    Vector scale(float, Vector);

    int equals(Vector, Vector);

    float distance(Vector, Vector);

#endif