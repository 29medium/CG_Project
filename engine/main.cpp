#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
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
int pointLineFill = 2; // 0-Point 1-Line 2-Fill
int color = 2; // 0-White 1-RGB 2-Random

int readXML(char * path){
    char final_path[1024];
    strcpy(final_path, "../xmlfiles/");
    strcat(final_path, path);

    XMLDocument doc;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(final_path);
    if(!eResult){
        element = doc.FirstChildElement()->FirstChildElement();
        for (; element; element = element->NextSiblingElement()) {
            string ficheiro = element->Attribute("file");
            char * file_name = const_cast<char *>(ficheiro.c_str());
            vector<string> tokens;
            ifstream file;
            file.open(file_name);
            if (file.is_open(), ios::in) {
                std::string line;
                char *token, *linha;
                float x, y, z;

                while (getline(file, line)) {
                    vector<string> tokens2;
                    stringstream check1(line);
                    string intermediate;

                    linha = const_cast<char *>(line.c_str());
                    token = strtok(linha, " ");
                    x=atof(token);

                    token = strtok(NULL, " ");
                    y=atof(token);

                    token = strtok(NULL, " ");
                    z=atof(token);

                    Point p = Point(x, y, z);
                    model.push_back(p);
                }
                file.close();
            }
            else {
                cout << "File didn't open" << endl;
                return 0;
            }
        }

    }
    else {
        cout << "File didn't load" << endl;
        return 0;
    }
    return 1;
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
        case 't':
            pointLineFill = (pointLineFill+1)%3;
            break;
        case 'c':
            color = (color+1)%3;
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void drawXYZ() {
    glBegin(GL_LINES);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.5, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.5, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.5);
    glEnd();
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

    drawXYZ();

    for(int i=0; i<model.size(); i+=3) {
        if(color==0)
            glColor3f(1, 1, 1);
        else if(color==2) {
            if (i % 9 == 0)
                glColor3f(1, 0, 0);
            else if(i%9 == 3)
                glColor3f(0,1,0);
            else
                glColor3f(0,0,1);
        } else
            glColor3f(sin(i),cos(i),1);

        glBegin(GL_TRIANGLES);
        glVertex3f(model[i].getX(),model[i].getY(),model[i].getZ());
        glVertex3f(model[i+1].getX(),model[i+1].getY(),model[i+1].getZ());
        glVertex3f(model[i+2].getX(),model[i+2].getY(),model[i+2].getZ());
        glEnd();
    }

    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    if(argc<2) {
        cout << "Wrong number of arguments" << endl;
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

    if(!readXML(argv[1]))
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
