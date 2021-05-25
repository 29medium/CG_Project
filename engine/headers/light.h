#ifndef _LIGHT_H_
#define _LIGHT_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class Light
{
    GLfloat position[4];

public:
    Light();
    Light(float *p);
    void renderLight();
};

#endif // _LIGHT_H_