#include "cone.h"

#define _USE_MATH_DEFINES
#include <math.h>

void drawBase(float radius, float height, int slices, int stacks, float sliceAngle, Shape* s) {
    int i;
    float alpha;

    for ( i = 0; i < slices; i++) {
        alpha = i * sliceAngle;

        s->addPoint(new Point(radius * cos(alpha + sliceAngle), 0, radius * sin(alpha + sliceAngle)));
        s->addPoint(new Point(0, 0, 0));
        s->addPoint(new Point(radius * cos(alpha), 0, radius * sin(alpha)));
    }
}

void drawSide(float radius, float height, int slices, int stacks, float sliceAngle, Shape* s) {
    int i, k;
    float alpha;
    float height_now = 0;
    float height_next = height / stacks;
    float radius_now = radius;
    float radius_next = radius - (radius / stacks);

    for (i = 0; i < slices; i++) {
        alpha = i * sliceAngle;
        for (k = 0; k < stacks; k++) {

            s->addPoint(new Point(radius_now * cos(alpha + sliceAngle), height_now, radius_now * sin(alpha + sliceAngle)));
            s->addPoint(new Point(radius_now * cos(alpha), height_now, radius_now * sin(alpha)));
            s->addPoint(new Point(radius_next * cos(alpha + sliceAngle), height_next, radius_next * sin(alpha + sliceAngle)));

            s->addPoint(new Point(radius_now * cos(alpha), height_now, radius_now * sin(alpha)));
            s->addPoint(new Point(radius_next * cos(alpha), height_next, radius_next * sin(alpha)));
            s->addPoint(new Point(radius_next * cos(alpha + sliceAngle), height_next, radius_next * sin(alpha + sliceAngle)));

            height_now = height_next;
            height_next += height / stacks;

            radius_now = radius_next;
            radius_next -= radius / stacks;
        }

        height_now = 0;
        height_next = height / stacks;

        radius_now = radius;
        radius_next = radius - (radius / stacks);
    }
}

Shape* cone(float radius, float height, int slices, int stacks) {
    Shape *s = new Shape();
    float sliceAngle = (2 * M_PI) / slices;

    drawBase(radius, height, slices, stacks, sliceAngle, s);
    drawSide(radius, height, slices, stacks, sliceAngle, s);

    return s;
}