#include "headers/box.h"

Point *box_textures(float a, float b, float max_a, float max_b)
{
    float x = (a + max_a / 2.0) / max_a;
    float y = (b + max_b / 2.0) / max_b;

    return new Point(y, x, 0);
}

void drawBackFront(float x, float y, float z, int divisions, Shape *s)
{
    float retangleX = x / divisions;
    float retangleY = y / divisions;
    float zFront = z / 2;
    float zBack = -zFront;
    float xLine = -(x / 2);
    float yLine = y / 2;
    int i, j;

    // Front and Back
    for (i = 0; i < divisions; i++)
    {
        for (j = 0; j < divisions; j++)
        {
            // Front
            s->addPoint(new Point(xLine, yLine, zFront));
            s->addNormal(new Point(0, 0, 1));
            s->addTexture(box_textures(yLine, xLine, y, x));

            s->addPoint(new Point(xLine, yLine - retangleY, zFront));
            s->addNormal(new Point(0, 0, 1));
            s->addTexture(box_textures(yLine - retangleY, xLine, y, x));

            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zFront));
            s->addNormal(new Point(0, 0, 1));
            s->addTexture(box_textures(yLine - retangleY, xLine + retangleX, y, x));

            s->addPoint(new Point(xLine, yLine, zFront));
            s->addNormal(new Point(0, 0, 1));
            s->addTexture(box_textures(yLine, xLine, y, x));

            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zFront));
            s->addNormal(new Point(0, 0, 1));
            s->addTexture(box_textures(yLine - retangleY, xLine + retangleX, y, x));

            s->addPoint(new Point(xLine + retangleX, yLine, zFront));
            s->addNormal(new Point(0, 0, 1));
            s->addTexture(box_textures(yLine, xLine + retangleX, y, x));

            // Back
            s->addPoint(new Point(xLine, yLine, zBack));
            s->addNormal(new Point(0, 0, -1));
            s->addTexture(box_textures(yLine, xLine, y, x));

            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zBack));
            s->addNormal(new Point(0, 0, -1));
            s->addTexture(box_textures(yLine - retangleY, xLine + retangleX, y, x));

            s->addPoint(new Point(xLine, yLine - retangleY, zBack));
            s->addNormal(new Point(0, 0, -1));
            s->addTexture(box_textures(yLine - retangleY, xLine, y, x));

            s->addPoint(new Point(xLine, yLine, zBack));
            s->addNormal(new Point(0, 0, -1));
            s->addTexture(box_textures(yLine, xLine, y, x));

            s->addPoint(new Point(xLine + retangleX, yLine, zBack));
            s->addNormal(new Point(0, 0, -1));
            s->addTexture(box_textures(yLine, xLine + retangleX, y, x));

            s->addPoint(new Point(xLine + retangleX, yLine - retangleY, zBack));
            s->addNormal(new Point(0, 0, -1));
            s->addTexture(box_textures(yLine - retangleY, xLine + retangleX, y, x));

            xLine += retangleX;
        }

        xLine = -(x / 2);
        yLine -= retangleY;
    }
}

void drawTopBottom(float x, float y, float z, int divisions, Shape *s)
{
    float yTop = y / 2;
    float yBottom = -yTop;
    float retangleX = x / divisions;
    float retangleZ = z / divisions;
    float xLine = x / 2;
    float zLine = z / 2;
    int i, j;

    // Top and Bottom
    for (i = 0; i < divisions; i++)
    {
        for (j = 0; j < divisions; j++)
        {
            // Top
            s->addPoint(new Point(xLine, yTop, zLine));
            s->addNormal(new Point(0, 1, 0));
            s->addTexture(box_textures(zLine, xLine, z, x));

            s->addPoint(new Point(xLine, yTop, zLine - retangleZ));
            s->addNormal(new Point(0, 1, 0));
            s->addTexture(box_textures(zLine - retangleZ, xLine, z, x));

            s->addPoint(new Point(xLine - retangleX, yTop, zLine));
            s->addNormal(new Point(0, 1, 0));
            s->addTexture(box_textures(zLine, xLine - retangleX, z, x));

            s->addPoint(new Point(xLine, yTop, zLine - retangleZ));
            s->addNormal(new Point(0, 1, 0));
            s->addTexture(box_textures(zLine - retangleZ, xLine, z, x));

            s->addPoint(new Point(xLine - retangleX, yTop, zLine - retangleZ));
            s->addNormal(new Point(0, 1, 0));
            s->addTexture(box_textures(zLine - retangleZ, xLine - retangleX, z, x));

            s->addPoint(new Point(xLine - retangleX, yTop, zLine));
            s->addNormal(new Point(0, 1, 0));
            s->addTexture(box_textures(zLine, xLine - retangleX, z, x));

            // Bottom
            s->addPoint(new Point(xLine, yBottom, zLine));
            s->addNormal(new Point(0, -1, 0));
            s->addTexture(box_textures(zLine, xLine, z, x));

            s->addPoint(new Point(xLine - retangleX, yBottom, zLine));
            s->addNormal(new Point(0, -1, 0));
            s->addTexture(box_textures(zLine, xLine - retangleX, z, x));

            s->addPoint(new Point(xLine, yBottom, zLine - retangleZ));
            s->addNormal(new Point(0, -1, 0));
            s->addTexture(box_textures(zLine - retangleZ, xLine, z, x));

            s->addPoint(new Point(xLine, yBottom, zLine - retangleZ));
            s->addNormal(new Point(0, -1, 0));
            s->addTexture(box_textures(zLine - retangleZ, xLine, z, x));

            s->addPoint(new Point(xLine - retangleX, yBottom, zLine));
            s->addNormal(new Point(0, -1, 0));
            s->addTexture(box_textures(zLine, xLine - retangleX, z, x));

            s->addPoint(new Point(xLine - retangleX, yBottom, zLine - retangleZ));
            s->addNormal(new Point(0, -1, 0));
            s->addTexture(box_textures(zLine - retangleZ, xLine - retangleX, z, x));

            xLine -= retangleX;
        }

        xLine = x / 2;
        zLine -= retangleZ;
    }
}

void drawLeftRight(float x, float y, float z, int divisions, Shape *s)
{
    float xRight = x / 2;
    float xLeft = -xRight;
    float yLine = y / 2;
    float zLine = z / 2;
    float retangleY = y / divisions;
    float retangleZ = z / divisions;
    int i, j;

    // Left and Right
    for (i = 0; i < divisions; i++)
    {
        for (j = 0; j < divisions; j++)
        {
            // Right
            s->addPoint(new Point(xRight, yLine, zLine));
            s->addNormal(new Point(1, 0, 0));
            s->addTexture(box_textures(yLine, zLine, y, z));

            s->addPoint(new Point(xRight, yLine - retangleY, zLine));
            s->addNormal(new Point(1, 0, 0));
            s->addTexture(box_textures(yLine - retangleY, zLine, y, z));

            s->addPoint(new Point(xRight, yLine - retangleY, zLine - retangleZ));
            s->addNormal(new Point(1, 0, 0));
            s->addTexture(box_textures(yLine - retangleY, zLine - retangleZ, y, z));

            s->addPoint(new Point(xRight, yLine, zLine));
            s->addNormal(new Point(1, 0, 0));
            s->addTexture(box_textures(yLine, zLine, y, z));

            s->addPoint(new Point(xRight, yLine - retangleY, zLine - retangleZ));
            s->addNormal(new Point(1, 0, 0));
            s->addTexture(box_textures(yLine - retangleY, zLine - retangleZ, y, z));

            s->addPoint(new Point(xRight, yLine, zLine - retangleZ));
            s->addNormal(new Point(1, 0, 0));
            s->addTexture(box_textures(yLine, zLine - retangleZ, y, z));

            // Left
            s->addPoint(new Point(xLeft, yLine, zLine));
            s->addNormal(new Point(-1, 0, 0));
            s->addTexture(box_textures(yLine, zLine, y, z));

            s->addPoint(new Point(xLeft, yLine - retangleY, zLine - retangleZ));
            s->addNormal(new Point(-1, 0, 0));
            s->addTexture(box_textures(yLine - retangleY, zLine - retangleZ, y, z));

            s->addPoint(new Point(xLeft, yLine - retangleY, zLine));
            s->addNormal(new Point(-1, 0, 0));
            s->addTexture(box_textures(yLine - retangleY, zLine, y, z));

            s->addPoint(new Point(xLeft, yLine, zLine));
            s->addNormal(new Point(-1, 0, 0));
            s->addTexture(box_textures(yLine, zLine, y, z));

            s->addPoint(new Point(xLeft, yLine, zLine - retangleZ));
            s->addNormal(new Point(-1, 0, 0));
            s->addTexture(box_textures(yLine, zLine - retangleZ, y, z));

            s->addPoint(new Point(xLeft, yLine - retangleY, zLine - retangleZ));
            s->addNormal(new Point(-1, 0, 0));
            s->addTexture(box_textures(yLine - retangleY, zLine - retangleZ, y, z));

            zLine -= retangleZ;
        }

        yLine -= retangleY;
        zLine = z / 2;
    }
}

Shape *box(float x, float y, float z, int divisions)
{
    Shape *s = new Shape();

    drawBackFront(x, y, z, divisions, s);
    drawTopBottom(x, y, z, divisions, s);
    drawLeftRight(x, y, z, divisions, s);

    return s;
}
