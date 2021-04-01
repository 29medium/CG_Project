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

void Point::add(Point *p) {
    x += p->getX();
    y += p->getY();
    z += p->getZ();
}

void Point::sub(Point *p) {
    x -= p->getX();
    y -= p->getY();
    z -= p->getZ();
}

void Point::multiply(float xx) {
    x *= xx;
    y *= xx;
    z *= xx;
}

Point* Point::clone() const {
    return new Point(x, y, z);
}

void Point::cross(Point *p) {
    float auxX = x, auxY = y, auxZ = z;

    x = auxY * p->getZ() - auxZ * p->getY();
    y = auxZ * p->getX() - auxX * p->getZ();
    z = auxX * p->getY() - auxY * p->getX();
}

void Point::normalize() {
    float vectorLength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    x /= vectorLength;
    y /= vectorLength;
    z /= vectorLength;
}


