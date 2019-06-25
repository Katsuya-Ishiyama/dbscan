#include <math.h>
#include "distance.h"

float EuclidDistance(Point *p1, Point *p2) {
    float distance;
    distance = sqrtf(powf(p1->x - p2->x, 2.0) + powf(p1->y - p2->y, 2.0));
    return distance;
}