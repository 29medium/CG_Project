#ifndef GENERATOR_TRANSFORMATION_H
#define GENERATOR_TRANSFORMATION_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

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

class Translation : public Transformation {
public:
    Translation(float xx, float yy, float zz);
    void transform();
};

class Rotation : public Transformation {
    float angle;
public:
    Rotation(float angle, float xx, float yy, float zz);
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
