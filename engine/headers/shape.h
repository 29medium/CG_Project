#ifndef __SHAPE_H__
#define __SHAPE_H__

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "point.h"

using namespace std;

class Shape
{
private:
    vector<Point *> points;

public:
    Shape();
    Shape(vector<Point *> p);
    void addPoint(Point *p);
    Point *getPoint(int i);
    int size();
    void draw();
};

#endif //__SHAPE_H__