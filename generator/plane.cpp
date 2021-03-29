#include "headers/plane.h"

Shape* plane(float size) {
    Shape *s = new Shape();

    float shapeSize = size / 2;

    s->addPoint(new Point(shapeSize, 0.0f, shapeSize));
    s->addPoint(new Point(-shapeSize, 0.0f, -shapeSize));
    s->addPoint(new Point(-shapeSize, 0.0f, shapeSize));

    s->addPoint(new Point(shapeSize, 0.0f, shapeSize));
    s->addPoint(new Point(shapeSize, 0.0f, -shapeSize));
    s->addPoint(new Point(-shapeSize, 0.0f, -shapeSize));

    return s;
}
