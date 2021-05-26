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

#ifdef __APPLE__
#include "/usr/local/include/IL/il.h"
#else
#include <IL/il.h>
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
    GLuint bufferT;
    vector<Transformation *> transf;
    vector<Shape *> models;
    vector<Group *> groups;
    Material *material;
    unsigned int texture;
    bool primary;
    const char *textureFile;

public:
    Group();

    Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g, Material *mat, bool p, const char *textureFile);

    // void renderSun();

    void render();

    static void renderGroups(vector<Group *> groups);

    void setBuffer();

    void setMaterial(Material *m);

    void loadImage(const char *texturefile);
};

#endif //GENERATOR_GROUP_H
