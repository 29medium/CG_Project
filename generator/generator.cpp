#include <stdlib.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <string.h>
#include <fstream>
#include "headers/plane.h"
#include "headers/box.h"
#include "headers/sphere.h"
#include "headers/cone.h"
#include "headers/torus.h"
//#include "headers/bezier.h"

using namespace std;

vector<Shape *> *parseBezier(const char *inputFile)
{
    vector<Point *> bezier_points;
    ifstream file(inputFile);
    string line;
    int patches_nr = 0, points_nr = 0;

    if (file.fail())
    {
        cout << "Couldn't find file: " << inputFile << "." << endl;
    }
    //nº patches
    getline(file, line);
    patches_nr = stoi(line);
    int patche_index[patches_nr][16];

    //percorrer linhas
    for (int i = 0; i < patches_nr; i++)
    {
        getline(file, line);

        for (int j = 0; j < 16; j++)
        {
            int split = line.find(",");
            string s = line.substr(0, split);
            patche_index[i][j] = stoi(s);
            line.erase(0, split + 1);
        }
    }

    //numero de pontos
    getline(file, line);
    points_nr = stoi(line);
    int cr[3];

    for (int i = 0; i < points_nr; i++)
    {
        getline(file, line);
        for (int j = 0; j < 3; j++)
        {
            int split = line.find(",");
            string s = line.substr(0, split);
            cr[j] = stof(s);
            line.erase(0, split + 1);
        }

        bezier_points.push_back(new Point(cr[0], cr[1], cr[2]));
    }

    vector<Shape *> *patches = new vector<Shape *>();

    for (int i = 0; i < patches_nr; i++)
    {
        Shape *p = new Shape();
        for (int j = 0; j < 16; j++)
        {
            Point *auxpoint = bezier_points.at(patche_index[i][j]);
            p->addPoint(
                new Point(
                    auxpoint->getX(),
                    auxpoint->getY(),
                    auxpoint->getZ()));
        }
        patches->push_back(p);
    }
    return patches;
}

Point *bValue(float u, Point *p0, Point *p1, Point *p2, Point *p3)
{
    float b0 = (1.0 - u) * (1.0 - u) * (1.0 - u);
    float b1 = 3.0 * u * (1.0 - u) * (1.0 - u);
    float b2 = 3 * u * u * (1.0 - u);
    float b3 = u * u * u;

    float x = p0->getX() * b0 + p1->getX() * b1 + p2->getX() * b2 + p3->getX() * b3;
    float y = p0->getY() * b0 + p1->getY() * b1 + p2->getY() * b2 + p3->getY() * b3;
    float z = p0->getZ() * b0 + p1->getZ() * b1 + p2->getZ() * b2 + p3->getZ() * b3;

    return new Point(x, y, z);
}

Point *bezierPatch(float u, float v, Shape *patch)
{
    Point *pts_u[4];
    Point *pts_v[4];

    int j = 0, k = 0;

    for (int i = 0; i < 16; i++)
    {
        Point *aux = patch->getPoint(i);
        pts_u[j] = aux;
        j++;

        if (j % 4 == 0)
        {
            pts_v[k++] = bValue(u, pts_u[0], pts_u[1], pts_u[2], pts_u[3]);

            j = 0;
        }
    }

    Point *res = bValue(v, pts_v[0], pts_v[1], pts_v[2], pts_v[3]);

    return res;
}

Shape *bezierPoints(vector<Shape *> *patches, int tessellation)
{
    float divisons = 1.0 / tessellation, u, u2, v, v2;
    Shape *s = new Shape();

    for (int i = 0; i < patches->size(); i++)
    {
        Shape *p = patches->at(i);

        for (int vs = 0; vs < tessellation; vs++)
        {
            for (int us = 0; us < tessellation; us++)
            {

                u = us * divisons;
                u2 = (us + 1) * divisons;
                v = vs * divisons;
                v2 = (vs + 1) * divisons;

                Point *p1 = bezierPatch(u, v, p);
                Point *p2 = bezierPatch(u2, v, p);
                Point *p3 = bezierPatch(u, v2, p);
                Point *p4 = bezierPatch(u2, v2, p);

                s->addPoint(p2);
                s->addPoint(p1);
                s->addPoint(p4);

                s->addPoint(p1);
                s->addPoint(p3);
                s->addPoint(p4);
            }
        }
    }
    return s;
}

void printFile(Shape *s, char *path)
{
    char buff[1024];
    char final_path[1024];
    int i;
    int size = s->size();
    Point *p;

    system("mkdir -p ../files/ ");
    strcpy(final_path, "../files/");
    strcat(final_path, path);
    ofstream file(final_path, std::ofstream::out);

    for (i = 0; i < size; i++)
    {
        p = s->getPoint(i);
        sprintf(buff, "%f %f %f\n", p->getX(), p->getY(), p->getZ());
        file << buff;
    }

    file.close();
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Not enough arguments" << endl;
        return 0;
    }

    Shape *s;
    char *path;

    if (strcmp(argv[1], "plane") == 0 && argc == 4)
    {
        s = plane(stof(argv[2]));
        path = argv[3];
    }
    else if (strcmp(argv[1], "box") == 0 && (argc == 6 || argc == 7))
    {
        s = box(stof(argv[2]), stof(argv[3]), stof(argv[4]), argc == 6 ? 1 : stoi(argv[5]));
        path = argc == 6 ? argv[5] : argv[6];
    }
    else if (strcmp(argv[1], "sphere") == 0 && argc == 6)
    {
        s = sphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4]));
        path = argv[5];
    }
    else if (strcmp(argv[1], "cone") == 0 && argc == 7)
    {
        s = cone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
        path = argv[6];
    }
    else if (strcmp(argv[1], "torus") == 0 && argc == 7)
    {
        s = torus(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
        path = argv[6];
    }
    else if (strcmp(argv[1], "bezier") == 0 && argc == 5)
    {
        int tessellation = atoi(argv[3]);
        if (tessellation >= 1)
        {
            vector<Shape *> *array = parseBezier(argv[2]);
            s = bezierPoints(array, tessellation);
        }
        path = argv[4];
    }
    else
    {
        cout << "Wrong Arguments" << endl;
        return 0;
    }
    printFile(s, path);
    cout << "File: " << path << endl;

    return 1;
}
