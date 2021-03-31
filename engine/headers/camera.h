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

using namespace std;

class Camera
{
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
    std::vector<float> cameraPosition;
    std::vector<float> cameraFront;
    std::vector<float> cameraUp;
    float cameraSpeed;

public:
    Camera();

    vector<float> getCameraPosition() const;

    vector<float> getCameraFront() const;

    vector<float> getCameraUp() const;

    float getCameraSpeed() const;

    // float getCamX() const;

    // float getCamY() const;

    // float getCamZ() const;

    float getCenterX() const;

    float getCenterY() const;

    float getCenterZ() const;

    void processNormalKeys(unsigned char key, int x, int y);

    void processMouseMotion(int xx, int yy);

    void processMouseButtons(int button, int state, int xx, int yy);

    void calculateCam();

    vector<float> multiplyVectorBySpeed(vector<float> vector);

    void addVectors(vector<float> v1, vector<float> v2);

    void subVectors(vector<float> v1, vector<float> v2);

    vector<float> crossVectors(vector<float> v1, vector<float> v2);

    vector<float> normalizeVector(vector<float> vector);
};

#endif //GENERATOR_CAMERA_H
