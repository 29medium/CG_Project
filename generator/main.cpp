#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <stdlib.h>
#include <GLUT/glut.h>
#else
#include <stdlib.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "plane.h"
#include "box.h"
#include "sphere.h"
#include "cone.h"
#include "../src/shape.h"
#include "../src/point.h"

using namespace std;

void printFile(Shape *s, char *path)
{
    char buff[1024];
    char final_path[1024];
    int i;
    int size = s->size();
    Point* p;

    system("mkdir -p ../files/ ");
    strcpy(final_path, "../files/");
    strcat(final_path, path);
    ofstream file(final_path, std::ofstream::out);

    for (i = 0; i < size; i++) {
        p = s->getPoint(i);
        sprintf(buff, "%f %f %f\n", p->getX(), p->getY(), p->getZ());
        file << buff;
    }

    file.close();
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    Shape* s;
    char* path;

    if (strcmp(argv[1], "plane") == 0 && argc == 4) {
        s = plane(atof(argv[2]));
        path = argv[3];
    }
    else if (strcmp(argv[1], "box") == 0 && (argc == 6 || argc == 7)) {
        s = box(atof(argv[2]), atof(argv[3]), atof(argv[4]), argc==6 ? 1 : atoi(argv[5]));
        path = argc==6 ? argv[5] : argv[6];
    }
    else if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
        s = sphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]));
        path = argv[5];
    }
    else if (strcmp(argv[1], "cone") == 0 && argc == 7) {
        s = cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]));
        path = argv[6];
    }
    else
        return 1;

    printFile(s, path);

    return 0;
}
