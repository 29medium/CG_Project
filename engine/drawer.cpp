//
// Created by Paulo Sousa on 13/03/2021.
//

#include "drawer.h"

void drawAxis(int axis) {
    float size = axis==1 ? 1.5 : 10;
    glBegin(GL_LINES);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(size, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, size, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, size);
    glEnd();
}

void drawShape(vector<Point> model, int color) {
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
}