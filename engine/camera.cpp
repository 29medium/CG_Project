#include "headers/camera.h"

Camera::Camera()
{
    defaultCam();
}

void Camera::defaultCam()
{
    startX = 400.0f;
    startY = 400.0f;
    alpha = -90.0f;
    beta = 0.0f;
    first_mouse = true;
    cameraPosition = new Point(-250.0f, 250.0f, 250.0f);
    cameraFront = new Point(1.0f, -1.0f, -1.0f);
    cameraUp = new Point(0.0f, 1.0f, 0.0f);
    speedMultiplier = 0.01f;
    mouseSensitivity = 1.0f;
}

float Camera::getCameraPositionX()
{
    return cameraPosition->getX();
}

float Camera::getCameraPositionY()
{
    return cameraPosition->getY();
}

float Camera::getCameraPositionZ()
{
    return cameraPosition->getZ();
}

float Camera::getCameraFrontX()
{
    return cameraFront->getX();
}

float Camera::getCameraFrontY()
{
    return cameraFront->getY();
}

float Camera::getCameraFrontZ()
{
    return cameraFront->getZ();
}

float Camera::getCameraUpX()
{
    return cameraUp->getX();
}

float Camera::getCameraUpY()
{
    return cameraUp->getY();
}

float Camera::getCameraUpZ()
{
    return cameraUp->getZ();
}

void Camera::setCameraSpeed(float cameraSpeed)
{
    this->cameraSpeed = cameraSpeed * speedMultiplier * 50;
}

Point *Camera::multiplyVectorBySpeed(Point *p) const
{
    Point *aux = p->clone();
    aux->multiply(cameraSpeed);
    return aux;
}

void Camera::addVectors(Point *p1, Point *p2)
{
    p1->add(p2);
}

void Camera::subVectors(Point *p1, Point *p2)
{
    p1->sub(p2);
}

Point *Camera::crossVectors(Point *p1, Point *p2)
{
    Point *aux = p1->clone();
    aux->cross(p2);
    return aux;
}

Point *Camera::normalizeVector(Point *p)
{
    Point *aux = p->clone();
    aux->normalize();
    return aux;
}

void Camera::processNormalKeys(unsigned char key, int x, int y)
{
    Point *v;

    switch (key)
    {
    case 'w':
        v = multiplyVectorBySpeed(cameraFront);
        addVectors(cameraPosition, v);
        break;
    case 'a':
        v = multiplyVectorBySpeed(normalizeVector(crossVectors(cameraFront, cameraUp)));
        subVectors(cameraPosition, v);
        break;
    case 's':
        v = multiplyVectorBySpeed(cameraFront);
        subVectors(cameraPosition, v);
        break;
    case 'd':
        v = multiplyVectorBySpeed(normalizeVector(crossVectors(cameraFront, cameraUp)));
        addVectors(cameraPosition, v);
        break;
    case 'r':
        defaultCam();
        break;
    case 'o':
        speedMultiplier *= 2;
        if (speedMultiplier > 0.01f)
            speedMultiplier = 0.01f;
        break;
    case 'p':
        speedMultiplier *= 0.5;
        if (speedMultiplier < 0.0001f)
            speedMultiplier = 0.0001f;
        break;
    case 'i':
        mouseSensitivity -= 0.4;
        if (mouseSensitivity < 0.4f)
            mouseSensitivity = 0.4f;
        break;
    case 'u':
        mouseSensitivity += 0.4;
        if (mouseSensitivity > 2.0f)
            mouseSensitivity = 2.0f;
        break;
    default:
        break;
    }
}

void Camera::processMouseMotion(int xx, int yy)
{
    if (first_mouse)
    {
        startX = xx;
        startY = yy;
        first_mouse = false;
    }

    float deltaX = (xx - startX) * mouseSensitivity;
    float deltaY = (startY - yy) * mouseSensitivity;
    startX = xx;
    startY = yy;

    alpha += deltaX;
    beta += deltaY;

    if (beta > 89.0f)
        beta = 89.0f;
    else if (beta < -89.0f)
        beta = -89.0f;

    cameraFront->update(cos(alpha * 3.14 / 180.0) * cos(beta * 3.14 / 180.0),
                        sin(beta * 3.14 / 180.0),
                        sin(alpha * 3.14 / 180.0) * cos(beta * 3.14 / 180.0));
    cameraFront->normalize();
}