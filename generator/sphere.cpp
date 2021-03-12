#define _USE_MATH_DEFINES
#include <cmath>
#include "sphere.h"


Shape* sphere(float radius, int slices, int stacks) {
    Shape* s = new Shape();

    float angleSt = M_PI / stacks;
    float angleSl = 2 * M_PI / slices;

    float alfa, b, beta_in, beta_out;

    for (int j = 0; j < stacks; j++) {
       
        b = 0.01 * j;
        alfa = j * (2 * M_PI / slices);

        beta_in = M_PI / 2;
        beta_out = beta_in - angleSt;

        for (int i = j; i < slices; i++) {

            if (i == 1) {
                s->addPoint(new Point(radius * cos(alfa) * cos(beta_out), radius * sin(beta_out), radius * sin(alfa) * cos(beta_out)));
                s->addPoint(new Point(0, radius, 0));
                s->addPoint(new Point(radius * cos(alfa + angleSl) * cos(beta_out), radius * sin(beta_out), radius * sin(alfa + angleSl) * cos(beta_out)));
                beta_in -= angleSt;
                beta_out -= angleSt;
            }
            else if (i == slices) {
                s->addPoint(new Point(0, -radius, 0));
                s->addPoint(new Point(radius * cos(alfa) * cos(beta_in), radius * sin(beta_in), radius * sin(alfa) * cos(beta_in)));
                s->addPoint(new Point(radius * cos(alfa + angleSl) * cos(beta_in), radius * sin(beta_in), radius * sin(alfa + angleSl) * cos(beta_in)));
                beta_in -= angleSt;
                beta_out -= angleSt;
            }
            else {
                s->addPoint(new Point(radius * cos(alfa) * cos(beta_in), radius * sin(beta_in), radius * sin(alfa) * cos(beta_in)));
                s->addPoint(new Point(radius * cos(alfa + angleSl) * cos(beta_in), radius * sin(beta_in), radius * sin(alfa + angleSl) * cos(beta_in)));
                s->addPoint(new Point(radius * cos(alfa + angleSl) * cos(beta_out), radius * sin(beta_out), radius * sin(alfa + angleSl) * cos(beta_out)));

                s->addPoint(new Point(radius * cos(alfa) * cos(beta_out), radius * sin(beta_out), radius * sin(alfa) * cos(beta_out)));
                s->addPoint(new Point(radius * cos(alfa) * cos(beta_in), radius * sin(beta_in), radius * sin(alfa) * cos(beta_in)));
                s->addPoint(new Point(radius * cos(alfa + angleSl) * cos(beta_out), radius * sin(beta_out), radius * sin(alfa + angleSl) * cos(beta_out)));

                beta_in -= angleSt;
                beta_out -= angleSt;
            }
        }

    }

    return s;
}