#include "headers/point.h"

Point::Point(float x1, float y1, float z1)
{
    x = x1;
    y = y1;
    z = z1;
}

float Point::getX()
{
    return x;
}

float Point::getY()
{
    return y;
}

float Point::getZ()
{
    return z;
}