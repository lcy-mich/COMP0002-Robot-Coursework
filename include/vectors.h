#ifndef VECTORS_H
    #define VECTORS_H

    typedef struct vector {
        int x;
        int y;
    } Vector;

    Vector add(Vector, Vector);

    Vector sub(Vector, Vector);

    Vector neg(Vector);

    Vector scale(float, Vector);

#endif