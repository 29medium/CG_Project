#include "headers/torus.h"

Point* pointCoord(float radiusIn, float radiusOut, float alpha, float beta) {
  return new Point((radiusOut + radiusIn * (cos(beta))) * cos(alpha),
                   (radiusOut + radiusIn * (cos(beta))) * sin(alpha),
                   radiusIn * sin(beta));;
}

Shape* drawRetangle(float radiusIn, float radiusOut, float alpha, float beta, float nextAlpha,float nextBeta, Shape* s) {

  s->addPoint(pointCoord(radiusIn, radiusOut, alpha, nextBeta));
  s->addPoint(pointCoord(radiusIn, radiusOut, alpha, beta));
  s->addPoint(pointCoord(radiusIn, radiusOut, nextAlpha, nextBeta));

  s->addPoint(pointCoord(radiusIn, radiusOut, nextAlpha, nextBeta));
  s->addPoint(pointCoord(radiusIn, radiusOut, alpha, beta));
  s->addPoint(pointCoord(radiusIn, radiusOut, nextAlpha, beta));

  return s;
}

Shape* torus(float radiusIn, float radiusOut, int slices, int layers)
{
    Shape* s = new Shape();
    float alpha, nextAlpha, beta, nextBeta;
    float sliceAngle = 2 * M_PI / slices;
    float layerAngle = 2 * M_PI / layers;

    for (int i = 0; i < layers; i++) {
        beta = i * layerAngle;
        nextBeta = (i+1) * layerAngle;

        for (int j = 0; j < slices; j++) {
            alpha = j * sliceAngle;
            nextAlpha = (j+1) * sliceAngle;

            drawRetangle(radiusIn, radiusOut, alpha, beta, nextAlpha, nextBeta, s);
        }
    }
    return s;
}
