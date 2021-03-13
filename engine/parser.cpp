//
// Created by Paulo Sousa on 13/03/2021.
//

#include "parser.h"

vector<Point> readXML(char * path){
    vector<Point> model;
    char final_path[1024];
    strcpy(final_path, "../xmlfiles/");
    strcat(final_path, path);

    XMLDocument doc;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(final_path);
    if(!eResult){
        for (element = doc.FirstChildElement()->FirstChildElement(); element; element = element->NextSiblingElement()) {
            string ficheiro = element->Attribute("file");
            char * file_name = const_cast<char *>(ficheiro.c_str());
            ifstream file;
            file.open(file_name);
            if (file.is_open(), ios::in) {
                string line;
                char *token, *linha;
                float x, y, z;

                while (getline(file, line)) {
                    linha = const_cast<char *>(line.c_str());
                    token = strtok(linha, " ");
                    x=atof(token);

                    token = strtok(NULL, " ");
                    y=atof(token);

                    token = strtok(NULL, " ");
                    z=atof(token);

                    Point p = Point(x, y, z);
                    model.push_back(p);
                }
                file.close();
            }
        }
    }
    else {
        cout << "File didn't load" << endl;
    }

    return model;
}