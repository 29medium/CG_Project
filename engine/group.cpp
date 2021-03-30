#include "headers/group.h"

Group::Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g) {
    transf = t;
    models = m;
    groups = g;
}

void Group::render() {
    for(int i=0; i<transf.size(); i++)
        transf[i]->transform();

    for(int i=0; i<models.size(); i++)
        models[i]->draw();

    for(int i=0; i<groups.size(); i++)
        groups[i]->render();
}

void Group::renderGroups(vector<Group *> groups) {
    for(int i=0; i<groups.size(); i++)
        groups[i]->render();
}
