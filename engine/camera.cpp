#include "headers/camera.h"

Camera::Camera() {
    alpha = 0.0f;
    beta = 0.0f;
    r=50.0f;
    radius = 100.0f;
    speed = 1.0f;
    tracking=0.0f;
    centerX = 0.0f;
    centerY = 0.0f;
    centerZ = 0.0f;
    camX = centerX + radius * cos(beta) * sin(alpha);
    camY = centerY + radius * sin(beta);
    camZ = centerZ + radius * cos(beta) * cos(alpha);
}

float Camera::getCamX() const {
    return camX;
}

float Camera::getCamY() const {
    return camY;
}

float Camera::getCamZ() const {
    return camZ;
}

float Camera::getCenterX() const {
    return centerX;
}

float Camera::getCenterY() const {
    return centerY;
}

float Camera::getCenterZ() const {
    return centerZ;
}

void Camera::processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            radius -= speed;
            break;
        case 'a':
            alpha -= M_PI/64;
            break;
        case 's':
            radius += speed;
            break;
        case 'd':
            alpha += M_PI/64;
            break;
        case 'q':
            beta -= M_PI/64;
            if(beta<(-(M_PI/2)+(M_PI/64)))
                beta = -(M_PI/2)+(M_PI/64);
            break;
        case 'e':
            beta += M_PI/64;
            if(beta>((M_PI/2)-(M_PI/64)))
                beta = (M_PI/2)-(M_PI/64);
            break;
        default:
            break;
    }
    calculateCam();
}

void Camera::processMouseButtons(int button, int state, int xx, int yy) {
    if (state == GLUT_DOWN)  {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}


void Camera::processMouseMotion(int xx, int yy) {
    float deltaX, deltaY;
    float alphaAux, betaAux;
    float rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {


        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }

    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}

void Camera::calculateCam() {
    camX = centerX + radius * cos(beta) * sin(alpha);
    camY = centerY + radius * sin(beta);
    camZ = centerZ + radius * cos(beta) * cos(alpha);
}
