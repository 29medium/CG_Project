#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include "tinyxml2.h"
#include "../src/shape.h"
#include "../src/point.h"

using namespace tinyxml2;
using namespace std;

// Global Variables
vector<Point> model;

void readXML(char * path){
    XMLDocument doc;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(path);// path2
    if(!eResult){
        element = doc.FirstChildElement()->FirstChildElement(); //<scene><model>
        for (; element; element = element->NextSiblingElement()) { // itera por os model
            string ficheiro = element->Attribute("file"); // pega no valor do atributo file  em cada  Model
            char * aux = const_cast<char *>(ficheiro.c_str());
            vector<string> tokens;
            ifstream file(aux);
            if (file.is_open()) {
                std::string line;
                while (getline(file, line)) {
                    vector<string> tokens2;
                    stringstream check1(line);
                    string intermediate;

                    while(getline(check1, intermediate, ' '))
                        tokens.push_back(intermediate);

                    float x=atof(tokens2[0].c_str());
                    float y=atof(tokens2[1].c_str());
                    float z=atof(tokens2[2].c_str());

                    Point p = Point(x, y, z);
                    model.push_back(p);
                }
                file.close();
            }
            else {
                cout << "File didn't open" << endl;
            }
        }

    }
    else {
        cout << "File didn't load" << endl;
    }
}

// Process Normal keys
void processNormalKeys(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
        default:
            break;
    }

    glutPostRedisplay();
}

// Process Special Keys
void processSpecialKeys(int key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
        default:
            break;
    }

    glutPostRedisplay();
}

// Draw XYZ axis
void drawXYZ() {
    glBegin(GL_LINES);

    // draw line for x axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.5, 0.0, 0.0);

    // draw line for y axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.5, 0.0);

    // draw line for Z axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.5);
    glEnd();
}

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
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
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    // draw XYZ axis
    drawXYZ();

    // geometric transformations
    //geometricTransformations();

    // put drawing instructions here
    for(int i=0; i<model.size(); i+=3) {
        glColor3f(sin(i),cos(i),1);
        glBegin(GL_TRIANGLES);
        glVertex3f(model[i].getX(),model[i].getY(),model[i].getZ());
        glVertex3f(model[i+1].getX(),model[i+1].getY(),model[i+1].getZ());
        glVertex3f(model[i+2].getX(),model[i+2].getY(),model[i+2].getZ());
        glEnd();
    }

    glEnd();

    // End of frame
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    if(argc<2)
        return 0;

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

    readXML(argv[1]);
    // Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
