#define _USE_MATH_DEFINES
#include <math.h>
#include "headers/sphere.h"

// Point* shpere_texture(float alpha,float beta) {
//     float du = (1.0 / (2.0*M_PI)) * (-alpha) + 1.0;
//     float dy = (1.0 / (M_PI)) * (beta + (M_PI / 2.0));

//     return new Point(du,dy);
// }

Shape *sphere(float radius, int slices, int stacks)
{
	Shape *s = new Shape();

	float angleSt = M_PI / stacks;
	float angleSl = (2 * M_PI) / slices;

	float rectAngle = (M_PI / 2);
	float beta;
	float alpha;

	for (int j = 0; j < stacks; j++)
	{
		beta = j * angleSt - rectAngle;

		for (int i = 0; i < slices; i++)
		{
			alpha = i * angleSl;

			Point *p1 = new Point(radius * cos(alpha) * cos(beta), radius * sin(beta), radius * sin(alpha) * cos(beta));
			s->addPoint(p1);
			p1->normalize();
			s->addNormal(p1);
			// s->addTexture(shpere_texture(alpha,beta));

			Point *p2 = new Point(radius * cos(alpha) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha) * cos(beta + angleSt));
			s->addPoint(p2);
			p2->normalize();
			s->addNormal(p2);
			// s->addTexture(shpere_texture(alpha,beta + angleSt));

			Point *p3 = new Point(radius * cos(alpha + angleSl) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSl) * cos(beta));
			s->addPoint(p3);
			p3->normalize();
			s->addNormal(p3);
			// s->addTexture(shpere_texture(alpha + angleSl,beta));

			Point *p4 = new Point(radius * cos(alpha) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha) * cos(beta + angleSt));
			s->addPoint(p4);
			p4->normalize();
			s->addNormal(p4);
			// s->addTexture(shpere_texture(alpha,beta + angleSt));

			Point *p5 = new Point(radius * cos(alpha + angleSl) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha + angleSl) * cos(beta + angleSt));
			s->addPoint(p5);
			p5->normalize();
			s->addNormal(p5);
			// s->addTexture(shpere_texture(alpha + angleSl,beta + angleSt));

			Point *p6 = new Point(radius * cos(alpha + angleSl) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSl) * cos(beta));
			s->addPoint(p6);
			p6->normalize();
			s->addNormal(p6);
			// s->addTexture(shpere_texture(alpha + angleSl,beta));
		}
	}

	return s;
}