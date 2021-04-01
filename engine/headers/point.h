#ifndef __POINT_H__
#define __POINT_H__

#include <math.h>

using namespace std;

class Point
{
private:
    float x;
    float y;
    float z;

public:
    Point(float x1, float y1, float z1);
    float getX();
    float getY();
    float getZ();
    void add(Point* p);
    void sub(Point* p);
    void multiply(float xx);
    void cross(Point* p);
    void normalize();

    Point *clone() const;
};

#endif //__POINT_H__