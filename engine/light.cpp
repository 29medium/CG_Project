#include "headers/light.h"

Light::Light(float *p)
{
    position[0] = p[0];
    position[1] = p[1];
    position[2] = p[2];
    position[3] = p[3];
}

void Light::renderLight()
{
    GLfloat ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[4] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat specular[4] = {1.0f, 1.0f, 1.0f, 1.0};

    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}