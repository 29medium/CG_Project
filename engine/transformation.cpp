#include <vector>
#include "headers/transformation.h"

Transformation::Transformation(float xx, float yy, float zz)
{
    x = xx;
    y = yy;
    z = zz;
}

float Transformation::getX() const
{
    return x;
}

float Transformation::getY() const
{
    return y;
}

float Transformation::getZ() const
{
    return z;
}

// Translation
DynamicTranslation::DynamicTranslation(float t, vector<Point *> catmullPoint) : Transformation(0, 0, 0)
{
    time = t;
    catmull = catmullPoint;

    float p[3];

    for (float gt = 0; gt < 1; gt += 0.01)
    {
        catmullRomPoint(gt, p, getCatmullPoints());
        orbit.push_back(new Point(p[0], p[1], p[2]));
    }
}

vector<Point *> DynamicTranslation::getCatmullPoints()
{
    return catmull;
}

void DynamicTranslation::transform(bool primary)
{
    if (primary)
    {
        glPushMatrix();
        glColor3f(1, 1, 1);
        drawCurve();
        glPopMatrix();
    }

    float coord[3] = {getX(), getY(), getZ()};

    float elapsed = (glutGet(GLUT_ELAPSED_TIME) % ((int)time)) / time;
    catmullRomPoint(elapsed, coord, getCatmullPoints());

    glTranslatef(coord[0], coord[1], coord[2]);
}

void DynamicTranslation::catmullRomPoint(float t, float *coord, vector<Point *> catmullpoints)
{
    int size = catmullpoints.size();

    float rt = t * size;
    int i = floor(rt);
    rt = rt - i;

    int index[4];
    index[0] = (i + size - 1) % size;
    index[1] = (index[0] + 1) % size;
    index[2] = (index[1] + 1) % size;
    index[3] = (index[2] + 1) % size;

    catmullCalculate(rt, index, coord, catmullpoints);
}

void DynamicTranslation::catmullCalculate(float t, int *index, float *p, std::vector<Point *> points)
{
    float aux[4];
    float t_2 = t * t;
    float t_3 = t * t * t;

    float m[4][4] = {{-0.5f, 1.5f, -1.5f, 0.5f},
                     {1.0f, -2.5f, 2.0f, -0.5f},
                     {-0.5f, 0.0f, 0.5f, 0.0f},
                     {0.0f, 1.0f, 0.0f, 0.0f}};

    p[0] = 0.0;
    p[1] = 0.0;
    p[2] = 0.0;

    aux[0] = t_3 * m[0][0] + t_2 * m[1][0] + t * m[2][0] + m[3][0];
    aux[1] = t_3 * m[0][1] + t_2 * m[1][1] + t * m[2][1] + m[3][1];
    aux[2] = t_3 * m[0][2] + t_2 * m[1][2] + t * m[2][2] + m[3][2];
    aux[3] = t_3 * m[0][3] + t_2 * m[1][3] + t * m[2][3] + m[3][3];

    int i_0 = index[0];
    int i_1 = index[1];
    int i_2 = index[2];
    int i_3 = index[3];
    Point *v0 = points[i_0];
    Point *v1 = points[i_1];
    Point *v2 = points[i_2];
    Point *v3 = points[i_3];

    p[0] = aux[0] * v0->getX() + aux[1] * v1->getX() + aux[2] * v2->getX() + aux[3] * v3->getX();
    p[1] = aux[0] * v0->getY() + aux[1] * v1->getY() + aux[2] * v2->getY() + aux[3] * v3->getY();
    p[2] = aux[0] * v0->getZ() + aux[1] * v1->getZ() + aux[2] * v2->getZ() + aux[3] * v3->getZ();
}

void DynamicTranslation::drawCurve()
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < orbit.size(); i++)
        glVertex3f(orbit[i]->getX(), orbit[i]->getY(), orbit[i]->getZ());

    glEnd();
}

// Static Translation

StaticTranslation::StaticTranslation(float xx, float yy, float zz) : Transformation(xx, yy, zz) {}

void StaticTranslation::transform(bool primary)
{
    glTranslatef(getX(), getY(), getZ());
}

// DynamicRotation
DynamicRotation::DynamicRotation(float t, float xx, float yy, float zz) : Transformation(xx, yy, zz)
{
    time = t;
}

void DynamicRotation::transform(bool primary)
{
    float angle = (glutGet(GLUT_ELAPSED_TIME) % ((int)time)) / time * 360;

    glRotatef(angle, getX(), getY(), getZ());
}

// StaticRotation
StaticRotation::StaticRotation(float a, float xx, float yy, float zz) : Transformation(xx, yy, zz)
{
    angle = a;
}

void StaticRotation::transform(bool primary)
{
    glRotatef(angle, getX(), getY(), getZ());
}

// Scale
Scale::Scale(float xx, float yy, float zz) : Transformation(xx, yy, zz) {}

void Scale::transform(bool primary)
{
    glScalef(getX(), getY(), getZ());
}

// Colour
Colour::Colour(float r, float g, float b) : Transformation(r, g, b) {}

void Colour::transform(bool primary)
{
    glColor3f(getX() / 255, getY() / 255, getZ() / 255);
}
