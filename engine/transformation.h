#ifndef GENERATOR_TRANSFORMATION_H
#define GENERATOR_TRANSFORMATION_H

#include <string>

using namespace std;

class Transformation {
private:
    string type;
    float angle;
    float x;
    float y;
    float z;
public:
    Transformation(string t, float a, float xx, float yy, float zz);
};

#endif //GENERATOR_TRANSFORMATION_H
