#include "headers/group.h"

Group::Group() {}

Group::Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g, Material *mat, bool p, const char *texturefile)
{
    transf = t;
    models = m;
    groups = g;
    material = mat;
    primary = p;
    texturefile = texturefile;
}

// void Group::renderSun()
// {

//     glPushMatrix();

//     for (int i = 0; i < transf.size(); i++)
//     {

//         // if (i == 0)
//         // {
//         //     GLfloat white[4] = {1, 1, 1, 1};

//         //     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
//         // }

//         transf[i]->transform(primary);
//     }

//     glPushMatrix();
//     material->draw();
//     glPopMatrix();

//     glBindBuffer(GL_ARRAY_BUFFER, buffer);
//     glVertexPointer(3, GL_FLOAT, 0, 0);
//     glBindBuffer(GL_ARRAY_BUFFER, bufferN);
//     glNormalPointer(GL_FLOAT, 0, 0);
//     glEnable(GL_LIGHTING);
//     glDrawArrays(GL_TRIANGLES, 0, buffer_size * 3);
//     glDisable(GL_LIGHTING);

//     glPopMatrix();
// }

void Group::render()
{
    glPushMatrix();

    for (int i = 0; i < transf.size(); i++)
    {

        transf[i]->transform(primary);
    }

    material->draw();

    glBindTexture(GL_TEXTURE_2D, texture);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferN);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferT);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    glEnable(GL_LIGHTING);
    glDrawArrays(GL_TRIANGLES, 0, buffer_size * 3);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);

    for (int i = 0; i < groups.size(); i++)
        groups[i]->render();

    glPopMatrix();
}

void Group::renderGroups(vector<Group *> groups)
{
    for (int i = 0; i < groups.size(); i++)
    {
        // if (i == 0)
        // {
        //     groups[i]->renderSun();
        // }
        // if (i == 0)
        // {
        //     GLfloat white[4] = {1, 1, 1, 1};

        //     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
        // }

        groups[i]->render();
    }
}

void Group::setBuffer()
{
    buffer_size = 0;

    for (int i = 0; i < models.size(); i++)
        buffer_size += models[i]->size();

    int index = 0, indext = 0;
    float *points_arr = (float *)malloc(sizeof(float) * buffer_size * 3);
    float *normais_arr = (float *)malloc(sizeof(float) * buffer_size * 3);
    //float *texturas_arr = (float *)malloc(sizeof(float) * buffer_size * 2);
    vector<float> texturas_arr;

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
            Point *auxT = models[i]->getTexture(j);
            //texturas_arr[indext] = auxT->getX();
            //texturas_arr[indext + 1] = auxT->getY();
            //indext += 2;
            texturas_arr.push_back(auxT->getX());
            texturas_arr.push_back(auxT->getY());
        }
    }

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size * 3, points_arr, GL_STATIC_DRAW);

    glGenBuffers(1, &bufferN);
    glBindBuffer(GL_ARRAY_BUFFER, bufferN);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size * 3, normais_arr, GL_STATIC_DRAW);

    glGenBuffers(1, &bufferT);
    glBindBuffer(GL_ARRAY_BUFFER, bufferT);
    glBufferData(GL_ARRAY_BUFFER, texturas_arr.size() * sizeof(float), &(texturas_arr[0]), GL_STATIC_DRAW);

    free(points_arr);
    free(normais_arr);

    //loadImage(textureFile);
}

void Group::loadImage(const char *texturefile)
{

    unsigned int t, tw, th;
    unsigned char *texData = NULL;

    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)texturefile);
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
}

void Group::setMaterial(Material *m)
{
    this->material = m;
}