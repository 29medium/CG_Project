#include "headers/plane.h"

Shape* plane(float size) {
    Shape *s = new Shape();

    float shapeSize = size / 2;

    s->addPoint(new Point(shapeSize, 0.0f, shapeSize));
    s->addNormal(new Point(0,1,0));
    s->addTexture(new Point(1,1));

    s->addPoint(new Point(-shapeSize, 0.0f, -shapeSize));
    s->addNormal(new Point(0,1,0));
    s->addTexture(new Point(-1,-1));

    s->addPoint(new Point(-shapeSize, 0.0f, shapeSize));
    s->addNormal(new Point(0,1,0));
    s->addTexture(new Point(-1,1));

    s->addPoint(new Point(shapeSize, 0.0f, shapeSize));
    normal->push_back(new Point(0,1,0));
    textures->push_back(new Point(1,1));

    s->addPoint(new Point(shapeSize, 0.0f, -shapeSize));
    normal->push_back(new Point(0,1,0));
    textures->push_back(new Point(1,-1));

    s->addPoint(new Point(-shapeSize, 0.0f, -shapeSize));
    s->addNormal(new Point(0,1,0));
    s->addTexture(new Point(-1,-1));

    return s;
}
