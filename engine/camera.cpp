#include "headers/camera.h"

Camera::Camera() {
    alpha = 0.0f;
    beta = 0.0f;
    radius = 100.0f;
    speed = 1.0f;
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

void Camera::calculateCam() {
    camX = centerX + radius * cos(beta) * sin(alpha);
    camY = centerY + radius * sin(beta);
    camZ = centerZ + radius * cos(beta) * cos(alpha);
}
