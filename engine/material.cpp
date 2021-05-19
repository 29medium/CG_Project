#include "headers/material.h"
#include <GL/glew.h>
#include <GL/glut.h>

Material::Material() {}

Material::Material(Transformation *d, Transformation *a, Transformation *s, Transformation *e)
{

    diffuse[3] = -1;
    ambient[3] = -1;

    if (d != NULL)
    {
        diffuse[0] = d->getX();
        diffuse[1] = d->getY();
        diffuse[2] = d->getZ();
        diffuse[0] = 1;
    }

    if (d != NULL)
    {
        diffuse[0] = d->getX();
        diffuse[1] = d->getY();
        diffuse[2] = d->getZ();
        diffuse[0] = 1;
    }
};