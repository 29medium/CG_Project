#include "headers/camera.h"

Camera::Camera() {
    cameraDefault();
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

void Camera::cameraDefault() {
    alpha = 0.0f;
    beta = 0.0f;
    radius = 250.0f;
    centerX = 0.0f;
    centerY = 0.0f;
    centerZ = 0.0f;
    camX = centerX + radius * cos(beta) * sin(alpha);
    camY = centerY + radius * sin(beta);
    camZ = centerZ + radius * cos(beta) * cos(alpha);
}

