#include "headers/transformation.h"

Transformation::Transformation(float xx, float yy, float zz) {
    x = xx;
    y = yy;
    z = zz;
}

float Transformation::getX() const {
    return x;
}

float Transformation::getY() const {
    return y;
}

float Transformation::getZ() const {
    return z;
}

// Translation
Translation::Translation(float xx, float yy, float zz) : Transformation(xx, yy, zz) {}

void Translation::transform() {
    glTranslatef(getX(), getY(), getZ());
}

// Rotation
Rotation::Rotation(float a, float xx, float yy, float zz) : Transformation(xx, yy, zz) {
    angle = a;
}

float Rotation::getAngle() const {
    return angle;
}

void Rotation::transform(){
    glRotatef(getAngle(), getX(), getY(), getZ());
}

// Scale
Scale::Scale(float xx, float yy, float zz) : Transformation(xx, yy, zz) {}

void Scale::transform() {
    glScalef(getX(), getY(), getZ());
}

// Colour
Colour::Colour(float r, float g, float b) : Transformation(r, g, b) {}

void Colour::transform() {
    glColor3f(getX()/255, getY()/255, getZ()/255);
}