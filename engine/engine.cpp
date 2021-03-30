#include <stdlib.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>
#include "headers/parser.h"
#include "headers/group.h"

using namespace tinyxml2;
using namespace std;

Group* group = nullptr;
int pointLineFill = 2; // 0-Point 1-Line 2-Fill
int axis = 0; // 0-No 1-Small 2-Big

int window;

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

void drawAxis(int a) {
    float size = a==1 ? 1.5 : 1000;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(size, 0.0, 0.0);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, size, 0.0);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, size);
    glEnd();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT_AND_BACK,pointLineFill==0 ? GL_POINT : (pointLineFill==1 ? GL_LINE : GL_FILL));

    if(axis)
        drawAxis(axis);

    group->render();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            glutDestroyWindow(window);
            exit(0);
        case 't':
            pointLineFill = (pointLineFill+1)%3;
            break;
        case 'v':
            axis = (axis+1)%3;
            break;
        case 'f':
            glutFullScreen();
            break;
        default:
            break;
    }

    glutPostRedisplay();
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
    window = glutCreateWindow("CG-TP14");

    group = parseXML(argv[1]);

    if(group == nullptr)
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
