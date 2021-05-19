#include "headers/shape.h"

Shape::Shape() {}

Shape::Shape(vector<Point *> p) {
    points = p;
}

void Shape::addPoint(Point *p)
{
    this->points.push_back(p);
}

void Shape::addNormal(Point *p)
{
    this->normal.push_back(p);
}

void Shape::addTexture(Point *p)
{
    this->texture.push_back(p);
}

Point *Shape::getPoint(int i)
{
    return this->points.at(i);
}


int Shape::size()
{
    return this->points.size();
}