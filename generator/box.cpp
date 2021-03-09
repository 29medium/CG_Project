#include "box.h"

void drawBackFront(float x, float y, float z, int divisions, Shape* s) {
    float retangleX = x / divisions;
    float retangleY = y / divisions;
    float zFront = z / 2;
    float zBack = -zFront;
    int i = 0;
    int j = 0;
    float xLine = x / 2;
    float yLine = y / 2;

    // Front and Back
    for ( i; i < divisions; i++) {
        for (j = 0; j < divisions; j++)
        {
            s->addPoint(new Point(xLine, yLine, zFront));
            s->addPoint(new Point(xLine, yLine - retangleY, zFront));
            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zFront));
            s->addPoint(new Point(xLine + retangleX, yLine, zFront));

            s->addPoint(new Point(xLine, yLine, zBack));
            s->addPoint(new Point(xLine, yLine - retangleY, zBack));
            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zBack));
            s->addPoint(new Point(xLine + retangleX, yLine, zBack));

            xLine += retangleX;
        }

        xLine = x/2;
        yLine -= retangleY;
    }
}

Shape* box(float x, float y, float z, int divisions) {
    Shape *s = new Shape();

    drawBackFront(x, y, z, divisions, s);
    
    return s;
}
