#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include "../src/shape.h"

float coordx = 0.0f;
float coordy = 0.0f;
float coordz = 0.0f;
float height = 3.0f;
float scale = 1;
float angle = 0.0f;

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawXYZ() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 100);
    glVertex3f(0, 0, -100);
    glEnd();
}

void drawPiramid() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    // fisrt triangle base
    glVertex3f(+1.0f, 0, +1.0f);
    glVertex3f(+1.0f, 0, -1.0f);
    glVertex3f(-1.0f, 0, -1.0f);

    // second triangle base
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, +1.0f);
    glVertex3f(+1.0f, 0.0f, +1.0f);

    // first face red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(+1.0f, 0.0f, +1.0f);
    glVertex3f(+1.0f, 0.0f, -1.0f);

    // second face green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(-1.0f, 0.0f, +1.0f);
    glVertex3f(+1.0f, 0.0f, +1.0f);

    // third face blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, +1.0f);

    // fourth face some color
    glColor3f(0.5f, 0.5f, 1.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(+1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);

    glScalef(1, scale, 1);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0,
        0.0, 0.0, 0.0,
        0.0f, 1.0f, 0.0f);
    drawXYZ();

    // put the geometric transformations here
    glTranslatef(coordx, coordy, coordz);
    glScalef(1, scale, 1);
    glRotatef(angle, 0, 1, 0);

    // put drawing instructions here
    drawPiramid();

    glEnd();

    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events
void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
    case 'w':
        coordx += 0.1f;
        break;
    case 's':
        coordx -= 0.1f;
        break;
    case 'a':
        coordz += 0.1f;
        break;
    case 'd':
        coordz -= 0.1f;
        break;
    case 'q':
        coordy += 0.1f;
        break;
    case 'e':
        coordy -= 0.1f;
        break;
    case '+':
        scale += 0.1f;
        break;
    case '-':
        scale -= 0.1f;
        break;
    case 'u':
        angle += 20.0f;
        break;
    case 'i':
        angle -= 20.0f;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    Shape s = Shape();
    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc(processNormalKeys);
    //glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
