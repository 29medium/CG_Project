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
