#ifndef GENERATOR_THORUS_H
#define GENERATOR_THORUS_H

#define _USE_MATH_DEFINES
#include <math.h>

#include "../../engine/headers/shape.h"
#include "../../engine/headers/point.h"

Shape* torus(float radiusIn, float radiusOut, int slice, int layers);

#endif //GENERATOR_THORUS_H
