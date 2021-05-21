#include "headers/group.h"

Group::Group() {}

Group::Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g, bool p)
{
    transf = t;
    models = m;
    groups = g;
    primary = p;
}

void Group::render()
{
    glPushMatrix();

    for (int i = 0; i < transf.size(); i++)
    {

        // if (i == 0)
        // {
        //     GLfloat white[4] = {1, 1, 1, 1};

        //     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
        // }

        transf[i]->transform(primary);
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferN);
    glNormalPointer(GL_FLOAT, 0, 0);
    glEnable(GL_LIGHTING);
    glDrawArrays(GL_TRIANGLES, 0, buffer_size * 3);
    glDisable(GL_LIGHTING);

    for (int i = 0; i < groups.size(); i++)
        groups[i]->render();

    glPopMatrix();
}

void Group::renderGroups(vector<Group *> groups)
{
    for (int i = 0; i < groups.size(); i++)
        groups[i]->render();
}

void Group::setBuffer()
{
    buffer_size = 0;

    for (int i = 0; i < models.size(); i++)
        buffer_size += models[i]->size();

    int index = 0;
    float *points_arr = (float *)malloc(sizeof(float) * buffer_size * 3);
    float *normais_arr = (float *)malloc(sizeof(float) * buffer_size * 3);

    for (int i = 0; i < models.size(); i++)
    {
        for (int j = 0; j < models[i]->size(); j++)
        {
            Point *aux = models[i]->getPoint(j);
            points_arr[index] = aux->getX();
            points_arr[index + 1] = aux->getY();
            points_arr[index + 2] = aux->getZ();

            Point *auxN = models[i]->getNormal(j);
            normais_arr[index] = auxN->getX();
            normais_arr[index + 1] = auxN->getY();
            normais_arr[index + 2] = auxN->getZ();
            index += 3;
        }
    }

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size * 3, points_arr, GL_STATIC_DRAW);

    glGenBuffers(1, &bufferN);
    glBindBuffer(GL_ARRAY_BUFFER, bufferN);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size * 3, normais_arr, GL_STATIC_DRAW);

    free(points_arr);
    free(normais_arr);
}