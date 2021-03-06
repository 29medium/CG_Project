#include "plane.h"

Shape* plane(float size) {
    Shape *s = new Shape();

    s->addPoint(size/2, 0.0f, size/2);
    s->addPoint(-size/2, 0.0f, -size/2);
    s->addPoint(-size/2, 0.0f, size/2);

    s->addPoint(size / 2, 0.0f, size / 2);
    s->addPoint(size / 2, 0.0f, -size / 2);
    s->addPoint(-size / 2, 0.0f, -size / 2);

    return s;
}
