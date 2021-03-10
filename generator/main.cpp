#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <stdlib.h>
#include <GLUT/glut.h>
#else
#include <stdlib.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include "plane.h"
#include "box.h"
#include "sphere.h"
#include "cone.h"
#include "../src/shape.h"
#include "../src/point.h"

using namespace std;

void printFile(Shape *s, char *file_path)
{
    char buff[1024];
    char path[1024];
    int i;
    int size = s->size();
    Point* p;

    system("mkdir -p ..\\files3d\\ ");
    strcpy(path, "..\\files3d\\");
    strcat(path, file_path);
    ofstream file(path, std::ofstream::out);

    for (i = 0; i < size; i++) {
        p = s->getPoint(i);
        sprintf(buff, "%f %f %f\n", p->getX(), p->getY(), p->getZ());
        file << buff;
    }

    file.close();
}

void help()
{
    cout << "HELP!!";
}

void generate_plane(float size, char *path)
{
    Shape *s = plane(size);
    printFile(s, path);
}

void generate_box(float x, float y, float z, int div, char *path)
{
    Shape *s = box(x, y, z, div);
    //printFile(s, path);
}

void generate_sphere(float radius, int slices, int stacks, char *path)
{
    Shape *s = sphere(radius, slices, stacks);
    printFile(s, path);
}

void generate_cone(float radius, float height, int slices, int stacks, char *path)
{
    Shape *s = cone(radius, height, slices, stacks);
    printFile(s, path);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }

    if (strcmp(argv[1], "--help") == 0)
    {
        help();
        return 0;
    }

    if (strcmp(argv[1], "plane") == 0 && argc == 4)
    {
        generate_plane(atof(argv[2]), argv[3]);
    }
    else if (strcmp(argv[1], "box") == 0 && (argc == 6 || argc == 7))
    {
        if (argc == 6)
            generate_box(atof(argv[2]), atof(argv[3]), atof(argv[4]), 1, argv[5]);
        else
            generate_box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), argv[6]);
    }
    else if (strcmp(argv[1], "sphere") == 0 && argc == 6)
    {
        generate_sphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
    }
    else if (strcmp(argv[1], "cone") == 0 && argc == 7)
    {
        generate_cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    }
    else
        return 1;

    return 0;
}
