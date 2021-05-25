#include "headers/point.h"

Point::Point(float x1, float y1, float z1)
{
    x = x1;
    y = y1;
    z = z1;
    type = 0;
}

Point::Point(float x1, float y1)
{
    x = x1;
    y = y1;
    type = 1;
}

float Point::getX() const
{
    return x;
}

float Point::getY() const
{
    return y;
}

float Point::getZ() const
{
    return z;
}

void Point::update(float x1, float y1, float z1)
{
    x = x1;
    y = y1;
    z = z1;
}

void Point::add(Point *p)
{
    x += p->getX();
    y += p->getY();
    z += p->getZ();
}

void Point::sub(Point *p)
{
    x -= p->getX();
    y -= p->getY();
    z -= p->getZ();
}

Point *Point::subPoint(Point *p)
{
    Point *point;
    float x1, y1, z1;
    x1 = x - p->getX();
    y1 = y - p->getY();
    z1 = z - p->getZ();

    point = new Point(x1, y1, z1);
}

void Point::multiply(float xx)
{
    x *= xx;
    y *= xx;
    z *= xx;
}

Point *Point::clone() const
{
    return new Point(x, y, z);
}

void Point::cross(Point *p)
{
    float auxX = x, auxY = y, auxZ = z;

    x = auxY * p->getZ() - auxZ * p->getY();
    y = auxZ * p->getX() - auxX * p->getZ();
    z = auxX * p->getY() - auxY * p->getX();
}

void Point::normalize()
{
    float vectorLength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    x /= vectorLength;
    y /= vectorLength;
    z /= vectorLength;
}

Point *Point::normalize3Points(Point *p1, Point *p2)
{
    Point *pAux = new Point(this->getX(), this->getY(), this->getZ());
    Point *v1, *v2;
    v1 = pAux->subPoint(p1);
    v2 = pAux->subPoint(p2);

    v1->cross(v2);
    v1->normalize();

    return v1;
}