#include <stdlib.h>

#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include "shape.h"
#include "transformation.h"

using namespace std;

class Group
{
private:
    float buffer_size;
    GLuint buffer;
    GLuint bufferN;
    vector<Transformation *> transf;
    vector<Shape *> models;
    vector<Group *> groups;
    Material *material;
    bool primary;

public:
    Group();

    Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g, Material *mat, bool p);

    // void renderSun();

    void render();

    static void renderGroups(vector<Group *> groups);

    void setBuffer();

    void setMaterial(Material *m);
};

#endif //GENERATOR_GROUP_H
