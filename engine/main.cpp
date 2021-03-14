#include <stdlib.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include <vector>
#include "../src/shape.h"
#include "parser.h"
#include "drawer.h"

using namespace tinyxml2;
using namespace std;

// Global Variables
vector<Point> model;
int pointLineFill = 2; // 0-Point 1-Line 2-Fill
int color = 2; // 0-White 1-RGB 2-Random
int axis = 1; // 0-No 1-Small 2-Big

void processNormalKeys(unsigned char key, int x, int y) {
    switch(key) {
        /*case 27:
            _exit(0);*/ 
        case 't':
            pointLineFill = (pointLineFill+1)%3;
            break;
        case 'c':
            color = (color+1)%3;
            break;
        case 'v':
            axis = (axis+1)%3;
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void changeSize(int w, int h) {
    if(h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT, pointLineFill==0 ? GL_POINT : (pointLineFill==1 ? GL_LINE : GL_FILL));

    if(axis)
        drawAxis(axis);

    drawShape(model, color);

    glutSwapBuffers();
}

void help() {
    cout << "C - Change Color" << endl;
    cout << "V - Toogle Axis" << endl;
    cout << "T - Change Polygon Mode" << endl;
    cout << "ESC - Exit" << endl;
}

int main(int argc, char **argv) {
    if(argc<2) {
        cout << "Wrong number of arguments" << endl;
        return 0;
    }

    if(!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h")) {
        help();
        return 2;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG-TP14");

    model = readXML(argv[1]);

    if(model.empty())
        return 1;

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(processNormalKeys);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutMainLoop();

    return 1;
}
