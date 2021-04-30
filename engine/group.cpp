#include "headers/group.h"

Group::Group() {}

Group::Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g)
{
    transf = t;
    models = m;
    groups = g;
}

void Group::render()
{

    for (int i = 0; i < transf.size(); i++)
        transf[i]->transform();

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, buffer_size * 3);

    for (int i = 0; i < groups.size(); i++)
    {
        glPushMatrix();
        groups[i]->render();
        glPopMatrix();
    }
}

void Group::renderGroups(vector<Group *> groups)
{

    for (int i = 0; i < groups.size(); i++)
    {
        glPushMatrix();
        groups[i]->render();
        glPopMatrix();
    }
}

void Group::setBuffer(){
    buffer_size = 0;

    for(int i=0; i<models.size(); i++)
        buffer_size += models[i]->size();

    int index = 0;
    float* points_arr = (float*) malloc(sizeof(float) * buffer_size * 3);

    for(int i=0; i<models.size(); i++){
        for(int j=0; j<models[i]->size(); j++) {
            Point *aux = models[i]->getPoint(j);
            points_arr[index] = aux->getX();
            points_arr[index+1] = aux->getY();
            points_arr[index+2] = aux->getZ();
            index+=3;
        }
    }

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size * 3, points_arr, GL_STATIC_DRAW);

    free(points_arr);
}