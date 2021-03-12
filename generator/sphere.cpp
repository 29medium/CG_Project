#define _USE_MATH_DEFINES
#include <cmath>
#include "sphere.h"


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
			s->addPoint(new Point(radius * cos(alpha) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha) * cos(beta + angleSt)));
			s->addPoint(new Point(radius * cos(alpha + angleSl) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSl) * cos(beta)));

			s->addPoint(new Point(radius * cos(alpha) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha) * cos(beta + angleSt)));
			s->addPoint(new Point(radius * cos(alpha + angleSl) * cos(beta + angleSt), radius * sin(beta + angleSt), radius * sin(alpha + angleSl) * cos(beta + angleSt)));
			s->addPoint(new Point(radius * cos(alpha + angleSl) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSl) * cos(beta)));
		}
	}

    return s;
}