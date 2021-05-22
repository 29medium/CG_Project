#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "point.h"
#include "transformation.h"

class Material
{

    float diffuse[4];
    float ambient[4];
    float specular[4];
    float emission[4];

public:
    Material();
    Material(Transformation *d, Transformation *a, Transformation *s, Transformation *e);
    void draw();
    float *getDiffuse();
    float *getAmbient();
    float *getSpecular();
    float *getEmission();
};

#endif