#define _USE_MATH_DEFINES
#include <math.h>
#include "headers/sphere.h"

Point* shpere_texture(float alpha,float beta) {
    float du = (1.0 / (2.0*M_PI)) * (-alpha) + 1.0;
    float dy = (1.0 / (M_PI)) * (beta + (M_PI / 2.0));

    return new Point(du,dy);
}

Shape* sphere(float radius, int slices, int stacks) {
    Shape* s = new Shape();

	float angleSt = M_PI / stacks;
	float angleSl = (2 * M_PI) / slices;

	float rectAngle = (M_PI / 2);
	float beta;
	float alpha;

	for (int j = 0; j < stacks; j++) {
		beta = j * angleSt - rectAngle;

		for (int i = 0; i < slices; i++) {
			alpha = i * angleSl;

			s->addPoint(new Point(radius * cos(alpha) * cos(beta), radius * sin(beta), radius * sin(alpha) * cos(beta)));
			s->addNormal(new Point(cos(alpha)*cos(beta),sin(beta),sin(alpha)*cos(beta)));
			s->addTexture(shpere_texture(alpha,beta));

			s->addPoint(new Point(radius * cos(alpha) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha) * cos(beta + angleSt)));
			s->addNormal(new Point(cos(alpha)*cos(beta + angleSt),sin(beta + angleSt),sin(alpha)*cos(beta + angleSt));
			s->addTexture(shpere_texture(alpha,beta + angleSt));

			s->addPoint(new Point(radius * cos(alpha + angleSl) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSl) * cos(beta)));
			s->addNormal(new Point(cos(alpha + angleSl)*cos(beta),sin(beta),sin(alpha + angleSl)*cos(beta)));
            s->addTexture(shpere_texture(alpha + angleSl,beta));


			s->addPoint(new Point(radius * cos(alpha) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha) * cos(beta + angleSt)));
			s->addNormal(new Point(cos(alpha)*cos(beta + angleSt),sin(beta + angleSt),sin(alpha)*cos(beta + angleSt)));
            s->addTexture(shpere_texture(alpha,beta + angleSt));

			s->addPoint(new Point(radius * cos(alpha + angleSl) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha + angleSl) * cos(beta + angleSt)));
			s->addNormal(new Point(cos(alpha + angleSl)*cos(beta + angleSt),sin(beta + angleSt),sin(alpha + angleSl)*cos(beta + angleSt)));
            s->addTexture(shpere_texture(alpha + angleSl,beta + angleSt));

			s->addPoint(new Point(radius * cos(alpha + angleSl) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSl) * cos(beta)));
			s->addNormal(new Point(cos(alpha + angleSl)*cos(beta),sin(beta),sin(alpha + angleSl)*cos(beta)));
            s->addTexture(shpere_texture(alpha + angleSl,beta));
		}
	}

    return s;
}