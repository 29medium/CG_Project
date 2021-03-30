#include "headers/group.h"

Group::Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g) {
    transf = t;
    models = m;
    groups = g;
}

vector<Transformation *> Group::getTransf() {
    return transf;
}

vector<Shape *> Group::getModels() {
    return models;
}

vector<Group *> Group::getGroups() {
    return groups;
}

void Group::render() {
    vector<Transformation*> transfsV = getTransf();
    for(int i=0; i<transfsV.size(); i++)
        transfsV[i]->transform();

    vector<Shape*> modelsV = getModels();
    for(int i=0; i<modelsV.size(); i++)
        modelsV[i]->draw();

    vector<Group*> subgroups = getGroups();
    for(int i=0; i<subgroups.size(); i++)
        subgroups[i]->render();
}