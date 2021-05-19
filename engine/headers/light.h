#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <GL/glut.h>

class Light
{
    float position[4];

public:
    Light(float *p);
    void renderLight();
};

#endif // _LIGHT_H_