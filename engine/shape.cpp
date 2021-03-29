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

void Shape::draw(int color) {
    for(int i=0; i<points.size(); i+=3) {
        if(color==0)
            glColor3f(1, 1, 1);
        else if(color==2) {
            if (i % 9 == 0)
                glColor3f(1, 0, 0);
            else if(i%9 == 3)
                glColor3f(0,1,0);
            else
                glColor3f(0,0,1);
        } else
            glColor3f(sin(i),cos(i),1);

        glBegin(GL_TRIANGLES);
        glVertex3f(points[i]->getX(),points[i]->getY(),points[i]->getZ());
        glVertex3f(points[i+1]->getX(),points[i+1]->getY(),points[i+1]->getZ());
        glVertex3f(points[i+2]->getX(),points[i+2]->getY(),points[i+2]->getZ());
        glEnd();
    }
}