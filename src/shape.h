#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>
#include "point.h"

class Shape {
private:
    std::vector<Point*> points;
public:
    void addPoint(Point *p);
};

#endif //__SHAPE_H__