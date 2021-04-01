#ifndef GENERATOR_CAMERA_H
#define GENERATOR_CAMERA_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>
#include "point.h"

using namespace std;

class Camera
{
private:
    float alpha;
    float beta;
    float r;
    float startX;
    float startY;
    float tracking;
    Point * cameraPosition;
    Point * cameraFront;
    Point * cameraUp;
    float cameraSpeed;

public:
    Camera();

    float getCameraPositionX();

    float getCameraPositionY();

    float getCameraPositionZ();

    float getCameraFrontX();

    float getCameraFrontY();

    float getCameraFrontZ();

    float getCameraUpX();

    float getCameraUpY();

    float getCameraUpZ();

    void processNormalKeys(unsigned char key, int x, int y);

    void processMouseMotion(int xx, int yy);

    void processMouseButtons(int button, int state, int xx, int yy);

    Point* multiplyVectorBySpeed(Point* p);

    void addVectors(Point* p1, Point* p2);

    void subVectors(Point* p1, Point* p2);

    Point* crossVectors(Point* p1, Point* p2);

    Point* normalizeVector(Point* p);
};

#endif //GENERATOR_CAMERA_H
