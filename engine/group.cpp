#include "group.h"

Group::Group(vector<Transformation *> t, vector<Shape *> m, vector<Group *> g) {
    transf = t;
    models = m;
    groups = g;
}

vector<Transformation *> Group::getTransformations() {
    return transf;
}

vector<Shape *> Group::getModels() {
    return models;
}

vector<Group *> Group::getGroups() {
    return groups;
}

void Group::setTransf(vector<Transformation *> transf) {
    Group::transf = transf;
}

void Group::setModels(vector<Shape *> models) {
    Group::models = models;
}

void Group::setGroups(vector<Group *> groups) {
    Group::groups = groups;
}
