#include "headers/material.h"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

Material::Material()
{
    for (int i = 0; i < 4; i++)
    {
        diffuse[i] = 0.1;
        ambient[i] = 0.1;
        specular[i] = 0.1;
        emission[i] = 0.1;
    }
}

Material::Material(Transformation *d, Transformation *a, Transformation *s, Transformation *e)
{

    diffuse[3] = -1;
    ambient[3] = -1;
    specular[3] = -1;
    emission[3] = -1;

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

    if (s != NULL)
    {
        specular[0] = s->getX();
        specular[1] = s->getY();
        specular[2] = s->getZ();
        specular[3] = 1;
    }

    if (e != NULL)
    {
        emission[0] = e->getX();
        emission[1] = e->getY();
        emission[2] = e->getZ();
        emission[3] = 1;
    }
}

float *Material::getDiffuse()
{
    return diffuse;
}

float *Material::getAmbient()
{
    return ambient;
}

float *Material::getSpecular()
{
    return specular;
}

float *Material::getEmission()
{
    return emission;
}

void Material::draw()
{
    if (diffuse[3] != 1)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    }

    if (ambient[3] != 1)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    }

    if (specular[3] != 1)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    }

    if (emission[3] != 1)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    }
}