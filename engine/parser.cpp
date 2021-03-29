#include "headers/parser.h"

Transformation * parseTranslate(XMLElement* element) {
    float x=0, y=0, z=0;

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    return new Translation(x, y, z);
}

Transformation * parseRotate(XMLElement* element) {
    float angle=0, x=0, y=0, z=0;

    if(element->Attribute("angle"))
        angle = stof(element->Attribute("angle"));

    if(element->Attribute("axisX"))
        x = stof(element->Attribute("axisX"));

    if(element->Attribute("axisY"))
        y = stof(element->Attribute("axisY"));

    if(element->Attribute("axisZ"))
        z = stof(element->Attribute("axisZ"));

    return new Rotation(angle, x, y, z);
}

Transformation * parseScale(XMLElement* element) {
    float x=0, y=0, z=0;

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    return new Translation(x, y, z);
}

vector<Shape *> parseModel(XMLElement* element) {
    vector<Shape *> model;

    for (XMLElement *elem = element->FirstChildElement("model"); elem; elem = elem->NextSiblingElement("model")) {
        vector<Point *> points;
        string path = elem->Attribute("file");
        char * file_name = const_cast<char *>(path.c_str());

        char final_path[1024];
        strcpy(final_path, "../files/");
        strcat(final_path, file_name);

        ifstream file;
        file.open(final_path);
        if (file.is_open(), ios::in) {
            string line;
            char *token, *lineC;
            float x, y, z;

            while (getline(file, line)) {
                lineC = const_cast<char *>(line.c_str());
                token = strtok(lineC, " ");
                x=stof(token);

                token = strtok(nullptr, " ");
                y=stof(token);

                token = strtok(nullptr, " ");
                z=stof(token);

                Point *p = new Point(x, y, z);
                points.push_back(p);
            }
            file.close();
        }
        Shape *shape = new Shape(points);
        model.push_back(shape);
    }

    return model;
}

Group* parseGroup(XMLElement* element) {
    vector<Transformation *> transf;
    vector<Group *> groups;
    vector<Shape *> models;

    for(XMLElement *elem = element->FirstChildElement(); elem; elem = elem->NextSiblingElement()) {
        if(strcmp(elem->Name(),"translate") == 0)
            transf.push_back(parseTranslate(element));
        if(strcmp(elem->Name(),"rotate") == 0)
            transf.push_back(parseRotate(element));
        if(strcmp(elem->Name(), "scale") == 0)
            transf.push_back(parseScale(element));
        if(strcmp(elem->Name(), "models") == 0)
            models = parseModel(elem);
        if(strcmp(elem->Name(), "groups") == 0)
            groups.push_back(parseGroup(elem));
    }

    return new Group(transf, models, groups);
}

Group* parseXML(char * path){
    Group* group;

    char final_path[1024];
    strcpy(final_path, "../xmlfiles/");
    strcat(final_path, path);

    XMLDocument doc;
    XMLNode *root;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(final_path);

    if(!eResult){
        if((root=doc.FirstChild())) {
            element = root->FirstChildElement("group");
            group = parseGroup(element);
        }
    }
    else {
        cout << "File " << path << " didn't load." << endl;
    }

    return group;
}