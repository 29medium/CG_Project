#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>
#include "point.h"

using namespace std;

class Shape
{
private:
    vector<Point *> points;

public:
    Shape(vector<Point *> p);
    void addPoint(Point *p);
    Point *getPoint(int i);
    int size();
};

#endif //__SHAPE_H__