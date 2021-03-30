#ifndef GENERATOR_CAMERA_H
#define GENERATOR_CAMERA_H

#include <math.h>

using namespace std;

class Camera {
private:
    float alpha;
    float beta;
    float radius;
    float speed;
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

    void calculateCam();
};

#endif //GENERATOR_CAMERA_H
