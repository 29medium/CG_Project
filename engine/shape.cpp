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

int Shape::size()
{
    return this->points.size();
}

void Shape::draw() {
    for(int i=0; i<points.size(); i+=3) {

        glBegin(GL_TRIANGLES);
        glVertex3f(points[i]->getX(),points[i]->getY(),points[i]->getZ());
        glVertex3f(points[i+1]->getX(),points[i+1]->getY(),points[i+1]->getZ());
        glVertex3f(points[i+2]->getX(),points[i+2]->getY(),points[i+2]->getZ());
        glEnd();
    }
}