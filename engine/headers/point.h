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
    int type; 

public:
    Point(float x1, float y1, float z1);
    Point(float x,float y);
    float getX() const;
    float getY() const;
    float getZ() const;
    void update(float x1, float y1, float z1);
    void add(Point *p);
    void sub(Point *p);
    Point *subPoint(Point *p);
    void multiply(float xx);
    void cross(Point *p);
    void normalize();
    Point *normalize3Points(Point *p1, Point *p2);

    Point *clone() const;
};

#endif //__POINT_H__