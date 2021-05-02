#include "headers/shape.h"

Shape::Shape() {}

Shape::Shape(vector<Point *> p) {
    points = p;
}

void Shape::addPoint(Point *p)
{
    this->points.push_back(p);
}

Point *Shape::getPoint(int i)
{
    return this->points.at(i);
}

vector<Point *> *Shape::getPoints()
{
    return this->points;
}

int Shape::size()
{
    return this->points.size();
}