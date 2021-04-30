#ifndef GENERATOR_TRANSFORMATION_H
#define GENERATOR_TRANSFORMATION_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#include "point.h"

class Transformation {
    float x;
    float y;
    float z;
public:
    Transformation(float xx, float yy, float zz);

    float getX() const;

    float getY() const;

    float getZ() const;

    virtual void transform() {};
};

class DynamicTranslation : public Transformation {
    float time;
    vector<Point*> catmull;
    vector<Point*> orbit;
public:
    DynamicTranslation(float t, vector<Point*> catmullPoints);
    void transform();
    float getTime() const;
    vector<Point*> getCatmullPoints();

    void catmullRomPoint(float t, float *coord, vector<Point *> catmullpoints);

    void catmullCalculate(float t, int *index, float *p, vector<Point *> points);

    void drawCurve();
};

class StaticTranslation : public Transformation {
public:
    StaticTranslation(float xx, float yy, float zz);
    void transform();
};

class DynamicRotation : public Transformation {
    float time;
public:
    DynamicRotation(float t, float xx, float yy, float zz);
    void transform();

    float getTime() const;
};

class StaticRotation : public Transformation {
    float angle;
public:
    StaticRotation(float angle, float xx, float yy, float zz);
    void transform();

    float getAngle() const;
};

class Scale : public Transformation {
public:
    Scale(float xx, float yy, float zz);
    void transform();
};

class Colour : public Transformation {
public:
    Colour(float r, float g, float b);
    void transform();
};

#endif //GENERATOR_TRANSFORMATION_H
