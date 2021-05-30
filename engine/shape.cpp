#include "headers/shape.h"

Shape::Shape() {}

Shape::Shape(vector<Point *> p)
{
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

Point *Shape::getNormal(int i)
{
    return this->normal.at(i);
}

void Shape::setNormal(vector<Point *> n)
{
    this->normal = n;
}

void Shape::setTexture(vector<Point *> t)
{
    this->texture = t;
}

void Shape::addTexture(Point *p)
{
    this->texture.push_back(p);
}

Point *Shape::getTexture(int i)
{
    return this->texture.at(i);
}

Point *Shape::getPoint(int i)
{
    return this->points.at(i);
}

int Shape::size()
{
    return this->points.size();
}