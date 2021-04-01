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
    float startX;
    float startY;
    bool first_mouse;
    Point * cameraPosition;
    Point * cameraFront;
    Point * cameraUp;
    float cameraSpeed;
    float speedMultiplier;
    float mouseSensitivity;

public:
    Camera();

    void defaultCam();

    float getCameraPositionX();

    float getCameraPositionY();

    float getCameraPositionZ();

    float getCameraFrontX();

    float getCameraFrontY();

    float getCameraFrontZ();

    float getCameraUpX();

    float getCameraUpY();

    float getCameraUpZ();

    Point* multiplyVectorBySpeed(Point* p) const;

    static void addVectors(Point* p1, Point* p2);

    static void subVectors(Point* p1, Point* p2);

    static Point* crossVectors(Point* p1, Point* p2);

    static Point* normalizeVector(Point* p);

    void processNormalKeys(unsigned char key, int x, int y);

    void processMouseMotion(int xx, int yy);

    void setCameraSpeed(float cameraSpeed);
};

#endif //GENERATOR_CAMERA_H
