#ifndef __POINT_H__
#define __POINT_H__

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
};

#endif //__POINT_H__