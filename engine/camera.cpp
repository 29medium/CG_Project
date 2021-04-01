#include "headers/camera.h"

Camera::Camera()
{
    alpha = 0.0f;
    beta = 0.0f;
    r = 50.0f;
    tracking = 0.0f;
    cameraPosition = new Point(0.0f, 0.0f, 10.0f);
    cameraFront = new Point(0.0f, 0.0f, -1.0f);
    cameraUp = new Point(0.0f, 1.0f, 0.0f);
    cameraSpeed = 1.0f;
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

Point *Camera::multiplyVectorBySpeed(Point *p)
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
    default:
        break;
    }
}

void Camera::processMouseButtons(int button, int state, int xx, int yy)
{
    if (state == GLUT_DOWN)
    {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP)
    {
        if (tracking == 1)
        {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2)
        {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}

void Camera::processMouseMotion(int xx, int yy)
{
    float deltaX, deltaY;
    float alphaAux, betaAux;
    float rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1)
    {

        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2)
    {
        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
}