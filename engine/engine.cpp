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
#include "headers/camera.h"

using namespace tinyxml2;
using namespace std;

vector<Group *> groups;
Camera *cam = nullptr;
int pointLineFill = 2;
int window;
bool fullscreen = false;
float deltaTime = 0.0f, currentFrame=0.0f, lastFrame = 0.0f;

int timebase;
float frames;
float fps;

void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void showFPS() {
    frames++;
    int time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase>1000){
        fps = frames*1000.0/(time-timebase);
        timebase = time;
        frames = 0;
    }
    char title[1024];
    sprintf(title,"FPS: %f",fps);
    glutSetWindowTitle(title);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    currentFrame = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    cam->setCameraSpeed(deltaTime);

    gluLookAt(cam->getCameraPositionX(), cam->getCameraPositionY(), cam->getCameraPositionZ(),
              cam->getCameraPositionX() + cam->getCameraFrontX(), cam->getCameraPositionY() + cam->getCameraFrontY(), cam->getCameraPositionZ() + cam->getCameraFrontZ(),
              cam->getCameraUpX(), cam->getCameraUpY(), cam->getCameraUpZ());

    glPolygonMode(GL_FRONT_AND_BACK, pointLineFill == 0 ? GL_POINT : (pointLineFill == 1 ? GL_LINE : GL_FILL));

    Group::renderGroups(groups);
    showFPS();

    glutSwapBuffers();
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        glutDestroyWindow(window);
        exit(0);
    case 't':
        pointLineFill = (pointLineFill + 1) % 3;
        break;
    case 'f':
        if (fullscreen)
        {
            glutReshapeWindow(1200, 900);
            glutPositionWindow(0, 0);
            fullscreen = false;
        }
        else
        {
            glutFullScreen();
            fullscreen = true;
        }
        break;
    default:
        cam->processNormalKeys(key, x, y);
        break;
    }

    glutPostRedisplay();
}

void processMouseMotion(int xx, int yy)
{
    cam->processMouseMotion(xx, yy);
}

void help()
{
    cout << "| ------------------------------------ |" << endl;
    cout << "| --------------- HELP --------------- |" << endl;
    cout << "| ------------------------------------ |" << endl;
    cout << "| W --------------------- Move Forward |" << endl;
    cout << "| S -------------------- Move Backward |" << endl;
    cout << "| A ------------------------ Move Left |" << endl;
    cout << "| D ----------------------- Move Right |" << endl;
    cout << "| R --------------------- Reset Camera |" << endl;
    cout << "| U ------------- Increase Sensitivity |" << endl;
    cout << "| I ------------- Decrease Sensitivity |" << endl;
    cout << "| O ------------------- Increase Speed |" << endl;
    cout << "| P ------------------- Decrease Speed |" << endl;
    cout << "| F ---------------- Toggle Fullscreen |" << endl;
    cout << "| T -------------- Change Polygon Mode |" << endl;
    cout << "| ESC --------------------------- Exit |" << endl;
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Wrong number of arguments" << endl;
        return 0;
    }

    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
    {
        help();
        return 2;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    window = glutCreateWindow("CG-TP14 Solar System");

    groups = parseXML(argv[1]);
    if (groups.empty())
        return 1;

    cam = new Camera();

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(processNormalKeys);
    glutMotionFunc(processMouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);

    init();

    timebase = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();

    return 1;
}
