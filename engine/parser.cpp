#include "headers/parser.h"

Transformation * parseTranslate(XMLElement* element) {
    float x = (element->Attribute("X") ? stof(element->Attribute("X")) : 0);
    float y = (element->Attribute("Y") ? stof(element->Attribute("Y")) : 0);
    float z = (element->Attribute("Z") ? stof(element->Attribute("Z")) : 0);

    return new Translation(x, y, z);
}

Transformation * parseRotate(XMLElement* element) {
    float angle = (element->Attribute("angle") ? stof(element->Attribute("angle")) : 0);
    float x = (element->Attribute("axiX") ? stof(element->Attribute("axisX")) : 0);
    float y = (element->Attribute("axisY") ? stof(element->Attribute("axisY")) : 0);
    float z = (element->Attribute("axisZ") ? stof(element->Attribute("axisZ")) : 0);

    return new Rotation(angle, x, y, z);
}

Transformation * parseScale(XMLElement* element) {
    float x = (element->Attribute("X") ? stof(element->Attribute("X")) : 1);
    float y = (element->Attribute("Y") ? stof(element->Attribute("Y")) : 1);
    float z = (element->Attribute("Z") ? stof(element->Attribute("Z")) : 1);

    return new Scale(x, y, z);
}

Transformation * parseColour(XMLElement* element) {
    float r = (element->Attribute("R") ? stof(element->Attribute("R")) : 0);
    float g = (element->Attribute("G") ? stof(element->Attribute("G")) : 0);
    float b = (element->Attribute("B") ? stof(element->Attribute("B")) : 0);

    return new Colour(r, g, b);
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
            char *lineC;
            float x, y, z;

            while (getline(file, line)) {
                lineC = const_cast<char *>(line.c_str());

                x=stof(strtok(lineC, " "));
                y=stof(strtok(nullptr, " "));
                z=stof(strtok(nullptr, " "));

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
            transf.push_back(parseTranslate(elem));
        if(strcmp(elem->Name(),"rotate") == 0)
            transf.push_back(parseRotate(elem));
        if(strcmp(elem->Name(), "scale") == 0)
            transf.push_back(parseScale(elem));
        if(strcmp(elem->Name(), "colour") == 0)
            transf.push_back(parseColour(elem));
        if(strcmp(elem->Name(), "models") == 0)
            models = parseModel(elem);
        if(strcmp(elem->Name(), "groups") == 0)
            groups.push_back(parseGroup(elem));
    }

    return new Group(transf, models, groups);
}

vector<Group *> parseXML(char * path){
    vector<Group *> groups;
    Group* group = nullptr;

    char final_path[1024];
    strcpy(final_path, "../xmlfiles/");
    strcat(final_path, path);

    XMLDocument doc;
    XMLNode *root;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(final_path);

    if(!eResult){
        if((root=doc.FirstChild())) {
            for(XMLElement *elem = root->FirstChildElement("group"); elem; elem = elem->NextSiblingElement("group")) {
                group = parseGroup(elem);
                groups.push_back(group);
            }
        }
    }
    else {
        cout << "File " << path << " didn't load." << endl;
    }

    return groups;
}