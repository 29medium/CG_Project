//
// Created by Paulo Sousa on 13/03/2021.
//

#ifndef GENERATOR_DRAWER_H
#define GENERATOR_DRAWER_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "../src/point.h"

using namespace std;

void drawAxis();
void drawShape(vector<Point> model, int color);

#endif //GENERATOR_DRAWER_H
