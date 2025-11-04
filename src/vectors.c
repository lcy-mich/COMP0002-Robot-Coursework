#include <vectors.h>

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

