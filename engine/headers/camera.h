#ifndef GENERATOR_CAMERA_H
#define GENERATOR_CAMERA_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

using namespace std;

class Camera {
private:
    float alpha;
    float beta;
    float radius;
    float r;
    float speed;
    float startX;
    float startY;
    float tracking;
    float camX;
    float camY;
    float camZ;
    float centerX;
    float centerY;
    float centerZ;
public:
    Camera();

    float getCamX() const;

    float getCamY() const;

    float getCamZ() const;

    float getCenterX() const;

    float getCenterY() const;

    float getCenterZ() const;

    void processNormalKeys(unsigned char key, int x, int y);

    void processMouseMotion(int xx, int yy);

    void processMouseButtons(int button, int state, int xx, int yy);

    void calculateCam();
};

#endif //GENERATOR_CAMERA_H
