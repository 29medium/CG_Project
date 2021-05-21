#include <stdlib.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>
#include "headers/parser.h"
#include "headers/group.h"
#include "headers/camera.h"
#include "headers/light.h"

Light::Light()
{
    position[0] = 0;
    position[1] = 0;
    position[2] = 0;
    position[3] = 1;
}

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
    GLfloat specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}