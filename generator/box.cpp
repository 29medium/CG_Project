#include "headers/box.h"

void drawBackFront(float x, float y, float z, int divisions, Shape* s) {
    float retangleX = x / divisions;
    float retangleY = y / divisions;
    float zFront = z / 2;
    float zBack = -zFront;
    float xLine = -(x / 2);
    float yLine = y / 2;
    int i, j;

    // Front and Back
    for ( i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++)
        {
            // Front
            s->addPoint(new Point(xLine, yLine, zFront));
            s->addPoint(new Point(xLine, yLine - retangleY, zFront));
            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zFront));

            s->addPoint(new Point(xLine, yLine, zFront));
            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zFront));
            s->addPoint(new Point(xLine + retangleX, yLine, zFront));

            // Back
            s->addPoint(new Point(xLine, yLine, zBack));
            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zBack));
            s->addPoint(new Point(xLine, yLine - retangleY, zBack));

            s->addPoint(new Point(xLine, yLine, zBack));
            s->addPoint(new Point(xLine + retangleX, yLine, zBack));
            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zBack));

            xLine += retangleX;
        }

        xLine = -(x / 2);
        yLine -= retangleY;
    }
}

void drawTopBottom(float x, float y, float z, int divisions, Shape* s) {
    float yTop = y / 2;
    float yBottom = -yTop;
    float retangleX = x / divisions;
    float retangleZ = z / divisions;
    float xLine = x / 2;
    float zLine = z / 2;
    int i, j;

    // Top and Bottom
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++)
        {
            // Top
            s->addPoint(new Point(xLine, yTop, zLine));
            s->addPoint(new Point(xLine, yTop, zLine - retangleZ));
            s->addPoint(new Point(xLine - retangleX, yTop, zLine));

            s->addPoint(new Point(xLine, yTop, zLine - retangleZ));
            s->addPoint(new Point(xLine - retangleX, yTop, zLine - retangleZ));
            s->addPoint(new Point(xLine - retangleX, yTop, zLine));

            // Bottom
            s->addPoint(new Point(xLine, yBottom, zLine));
            s->addPoint(new Point(xLine - retangleX, yBottom, zLine));
            s->addPoint(new Point(xLine, yBottom, zLine - retangleZ));

            s->addPoint(new Point(xLine, yBottom, zLine - retangleZ));
            s->addPoint(new Point(xLine - retangleX, yBottom, zLine));
            s->addPoint(new Point(xLine - retangleX, yBottom, zLine - retangleZ));

            xLine -= retangleX;
        }

        xLine = x / 2;
        zLine -= retangleZ;
    }
}

void drawLeftRight(float x, float y, float z, int divisions, Shape* s) {
    float xRight = x / 2;
    float xLeft = -xRight;
    float yLine = y / 2;
    float zLine = z / 2;
    float retangleY = y / divisions;
    float retangleZ = z / divisions;
    int i, j;

    // Left and Right
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++)
        {
            // Right
            s->addPoint(new Point(xRight, yLine, zLine));
            s->addPoint(new Point(xRight, yLine - retangleY, zLine));
            s->addPoint(new Point(xRight, yLine - retangleY, zLine - retangleZ));

            s->addPoint(new Point(xRight, yLine, zLine));
            s->addPoint(new Point(xRight, yLine - retangleY, zLine - retangleZ));
            s->addPoint(new Point(xRight, yLine, zLine - retangleZ));

            // Left
            s->addPoint(new Point(xLeft, yLine, zLine));
            s->addPoint(new Point(xLeft, yLine - retangleY, zLine - retangleZ));
            s->addPoint(new Point(xLeft, yLine - retangleY, zLine));

            s->addPoint(new Point(xLeft, yLine, zLine));
            s->addPoint(new Point(xLeft, yLine, zLine - retangleZ));
            s->addPoint(new Point(xLeft, yLine - retangleY, zLine - retangleZ));

            zLine -= retangleZ;
        }

        yLine -= retangleY;
        zLine = z / 2;
    }
}

Shape* box(float x, float y, float z, int divisions) {
    Shape *s = new Shape();

    drawBackFront(x, y, z, divisions, s);
    drawTopBottom(x, y, z, divisions, s);
    drawLeftRight(x, y, z, divisions, s);
    
    return s;
}
