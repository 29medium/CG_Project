#include <stdlib.h>

#ifndef __SHAPE_H__
#define __SHAPE_H__

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include "point.h"
#include "material.h"

using namespace std;

class Shape
{
private:
    vector<Point *> points;
    vector<Point *> normal;
    vector<Point *> texture;
    Material *material;

public:
    Shape();
    Shape(vector<Point *> p);
    void addPoint(Point *p);
    void addNormal(Point *p);
    void setNormal(vector<Point *> n);
    void setTexture(vector<Point *> t);
    void addTexture(Point *p);
    Point *getPoint(int i);
    Point *getNormal(int i);
    Point *getTexture(int i);
    int size();
};

#endif //__SHAPE_H__