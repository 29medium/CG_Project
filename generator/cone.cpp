#include "headers/cone.h"

#define _USE_MATH_DEFINES
#include <math.h>

// Point * getNormalCone(float edge [3], Point * p, float tangAlpha){
//     float point_aux[3];

//     // p->get(point_aux);

//     point_aux[0] = p->getX();
//     point_aux[1] = p->getY();
//     point_aux[2] = p->getZ();

//     float distance = dist_2_P(edge,point_aux);

//     float height = quadratic_equation(distance*tangAlpha,point_aux);

//     float res [3];
//     float point_at_aixis [3] = {0.0,height,0.0};
//     vector_between_normalized(point_at_aixis,point_aux,res);
//     return new Point(res[0],res[1],res[2]);
// }

void drawBase(float radius, float height, int slices, int stacks, float sliceAngle, Shape *s)
{
    int i;
    float alpha;

    for (i = 0; i < slices; i++)
    {
        alpha = i * sliceAngle;

        s->addPoint(new Point(radius * cos(alpha + sliceAngle), 0, radius * sin(alpha + sliceAngle)));
        s->addNormal(new Point(0.0, -1.0, 0.0));
        s->addPoint(new Point(0, 0, 0));
        s->addNormal(new Point(0.0, -1.0, 0.0));
        s->addPoint(new Point(radius * cos(alpha), 0, radius * sin(alpha)));
        s->addNormal(new Point(0.0, -1.0, 0.0));
    }
}

void drawSide(float radius, float height, int slices, int stacks, float sliceAngle, Shape *s)
{
    int i, k;
    float alpha;
    float height_now = 0;
    float height_next = height / stacks;
    float radius_now = radius;
    float radius_next = radius - (radius / stacks);
    float edge[3] = {0.0, height, 0.0};
    float tangAlpha = radius / height;

    Point *p1, *p2, *p3;

    for (i = 0; i < slices; i++)
    {
        alpha = i * sliceAngle;
        for (k = 0; k < stacks; k++)
        {
            p1 = new Point(radius_now * cos(alpha + sliceAngle), height_now, radius_now * sin(alpha + sliceAngle));
            p2 = new Point(radius_now * cos(alpha), height_now, radius_now * sin(alpha));
            p3 = new Point(radius_next * cos(alpha + sliceAngle), height_next, radius_next * sin(alpha + sliceAngle));

            s->addPoint(p1);
            // s->addNormal(getNormalCone(edge,p1,tangAlpha));

            s->addPoint(p2);
            // s->addNormal(getNormalCone(edge,p1,tangAlpha));

            s->addPoint(p3);
            // s->addNormal(getNormalCone(edge,p1,tangAlpha));

            p1 = new Point(radius_now * cos(alpha), height_now, radius_now * sin(alpha));
            p2 = new Point(radius_next * cos(alpha), height_next, radius_next * sin(alpha));
            p3 = new Point(radius_next * cos(alpha + sliceAngle), height_next, radius_next * sin(alpha + sliceAngle));

            s->addPoint(p1);
            // s->addNormal(getNormalCone(edge,p1,tangAlpha));

            s->addPoint(p2);
            // s->addNormal(getNormalCone(edge,p1,tangAlpha));

            s->addPoint(p3);
            // s->addNormal(getNormalCone(edge,p1,tangAlpha));

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

Shape *cone(float radius, float height, int slices, int stacks)
{
    Shape *s = new Shape();
    float sliceAngle = (2 * M_PI) / slices;

    drawBase(radius, height, slices, stacks, sliceAngle, s);
    drawSide(radius, height, slices, stacks, sliceAngle, s);

    return s;
}