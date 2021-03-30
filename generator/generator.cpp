#include <stdlib.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream.h>
#include <string.h>
#include <fstream.h>
#include "headers/plane.h"
#include "headers/box.h"
#include "headers/sphere.h"
#include "headers/cone.h"
#include "headers/torus.h"

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
    if (argc < 2) {
        cout << "Not enough arguments" << endl;
        return 0;
    }

    Shape* s;
    char* path;

    if (strcmp(argv[1], "plane") == 0 && argc == 4) {
        s = plane(stof(argv[2]));
        path = argv[3];
    }
    else if (strcmp(argv[1], "box") == 0 && (argc == 6 || argc == 7)) {
        s = box(stof(argv[2]), stof(argv[3]), stof(argv[4]), argc==6 ? 1 : stoi(argv[5]));
        path = argc==6 ? argv[5] : argv[6];
    }
    else if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
        s = sphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4]));
        path = argv[5];
    }
    else if (strcmp(argv[1], "cone") == 0 && argc == 7) {
        s = cone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
        path = argv[6];
    }
    else if (strcmp(argv[1], "torus") == 0 && argc == 7) {
        s = torus(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
        path = argv[6];
    }
    else {
        cout << "Wrong Arguments" << endl;
        return 0;
    }

    printFile(s, path);
    cout << "File: " << path << endl;

    return 1;
}
