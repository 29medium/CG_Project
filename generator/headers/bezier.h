
#ifndef _BEZIER_H
#define _BEZIER_H


#include "Point.h"
#include <vector>

class Patch {
    vector<Point *> * control_p;

public:
    Patch();
    vector<Point *> * getControlP();
    void addControlP(Point * p);
    Point * getPoint(int i);
    ~Patch();
};

vector<Patch *>* parseBezier(const char* inputFile);
void bezierPoints(vector<Patch *> * patches, int tessellation);
void write_file(string file_name,vector<Point*> * vertices);


#endif //GENERATOR_BEZIER_H