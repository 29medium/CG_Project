#include "headers/torus.h"

Point * torus_texture(int slices,int stacks,int i,int j){
    float dx = 1.0 / stacks;
    float dy = 1.0/  slices;

    return new Point((-i*dx) + 1.0,j*dy);
  }

Point *pointCoord(float radiusIn, float radiusOut, float alpha, float beta)
{
  return new Point((radiusOut + radiusIn * (cos(beta))) * cos(alpha),
                   (radiusOut + radiusIn * (cos(beta))) * sin(alpha),
                   radiusIn * sin(beta));
}

Shape *drawRetangle(float radiusIn, float radiusOut, float alpha, float beta, float nextAlpha, float nextBeta, Shape *s,int i,int j,int slices,int layers)
{

  s->addPoint(pointCoord(radiusIn, radiusOut, alpha, nextBeta));
  s->addNormal(pointCoord(1, 1, alpha, nextBeta));
  s->addTexture(torus_texture(slices,layers,i,j));
  s->addPoint(pointCoord(radiusIn, radiusOut, alpha, beta));
  s->addNormal(pointCoord(1, 1, alpha, beta));
  s->addTexture(torus_texture(slices,layers,i,j+1));
  s->addPoint(pointCoord(radiusIn, radiusOut, nextAlpha, nextBeta));
  s->addNormal(pointCoord(1, 1, nextAlpha, nextBeta));
  s->addTexture(torus_texture(slices,layers,i+1,j));

  s->addPoint(pointCoord(radiusIn, radiusOut, nextAlpha, nextBeta));
  s->addNormal(pointCoord(1, 1, nextAlpha, nextBeta));
  s->addTexture(torus_texture(slices,layers,i,j+1));
  s->addPoint(pointCoord(radiusIn, radiusOut, alpha, beta));
  s->addNormal(pointCoord(1, 1, alpha, beta));
  s->addTexture(torus_texture(slices,layers,i+1,j+1));
  s->addPoint(pointCoord(radiusIn, radiusOut, nextAlpha, beta));
  s->addNormal(pointCoord(1, 1, nextAlpha, beta));
  s->addTexture(torus_texture(slices,layers,i+1,j));

  return s;
}

Shape *torus(float radiusIn, float radiusOut, int slices, int layers)
{
  Shape *s = new Shape();
  float alpha, nextAlpha, beta, nextBeta;
  float sliceAngle = 2 * M_PI / slices;
  float layerAngle = 2 * M_PI / layers;

  for (int i = 0; i < layers; i++)
  {
    beta = i * layerAngle;
    nextBeta = (i + 1) * layerAngle;

    for (int j = 0; j < slices; j++)
    {
      alpha = j * sliceAngle;
      nextAlpha = (j + 1) * sliceAngle;

      drawRetangle(radiusIn, radiusOut, alpha, beta, nextAlpha, nextBeta, s,i,j,slices,layers);
    }
  }
  return s;
}
