#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <GL/glut.h>

class Light
{
    GLfloat position[4];

public:
    Light();
    Light(float *p);
    void renderLight();
};

#endif // _LIGHT_H_