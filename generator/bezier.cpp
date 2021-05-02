#include "headers/bezier.h"

Patch::Patch() {
    control_p = new vector<Point*>();
}

vector<Point *> * Patch::getControlP(){
    return control_p;
}

void Patch::addControlP(Point * p){
    control_p->push_back(p);
}

Patch::~Patch(){
    delete(control_p);
}

Point * Patch::getPoint(int i){
    return control_p->at(i);
}

void write_file(string file_name,vector<Point*> * vertices){

    system("mkdir -p ../files/ ");
    string path = "../files/" + file_name;

    ofstream outputFile;
    outputFile.open(path);

    vector<Point*>::iterator it;
    for(it = vertices->begin(); it != vertices->end(); it++){
        outputFile << (*(*it)).to_String() << endl;
    }

    outputFile.close();
}

vector<Patch *>* parseBezier(const char* inputFile) {
    vector<Point *> bezier_points;
    ifstream file(inputFile);
    string line;
    int patches_nr = 0, points_nr = 0;

    ifstream file(patch_path);

    if (file.fail()) {
        cout<< "Couldn't find file: " << patch_path  << "." << endl;
    }
    //nº patches
    getline(file,line);
    patches_nr = stoi(line);
    int patche_index [patches_nr][16];

    //percorrer linhas
    for (int i = 0; i < patches_nr; i++) {
        getline(file, line);

        for(int j = 0; j < 16; j++){
            int split = line.find(",");
            string s = line.substr(0,split);
            patche_index[i][j] = stoi(s);
            line.erase(0,split+1);
        }
    }

    //numero de pontos
    getline(file, line);
    points_nr = stoi(line);
    int cr[3]

    for (int i = 0; i < points_nr; i++) {
        getline(file, line);
        for(int j = 0; j < 3; j++){
            int split = line.find(",");
            string s = line.substr(0,split);
            cr[j] = stof(s);
            line.erase(0,split+1);
        }

        bezier_points.push_back(new Point(cr[0],cr[1],cr[2]));
    }

    vector<Patch *> * patches = new vector<Patch*>();

    for(int i = 0; i < patches_nr; i++){
        Patch * p = new Patch();
        for(int j = 0; j < 16; j++){
            Point * auxpoint = bezier_points.at(patche_index[i][j]);
            p->addControlP(
                    new Point(
                    auxpoint->getX(),
                    auxpoint->getY(),
                    auxpoint->getZ())
                    );
        }
        patches->push_back(p);
    }
    return patches;
}

Shape* bezierPoints(vector<Patch *> * patches, int tessellation){
    float divisons = 1.0 / tessellation,u,u2,v,v2;
    Shape* s = new Shape();

    for(int i = 0; i < patches->size(); i++) {
        Patch * p = patches->getPoint(i);

        for (int r = 0; r < tessellation; r++) {
            for (int j = 0; j < tessellation; j++) {

                u = j * divisons;
                v = r * divisons;
                u2 = (j+1) * divisons;
                v2 = (r+1) * divisons;

                Point * p1 = bezierPatch(u,v,p);
                Point * p2 = bezierPatch(u2,v,p);
                Point * p3 = bezierPatch(u,v2,p);
                Point * p4 = bezierPatch(u2,v2,p);


                s->push_back(p2);
                s->push_back(p1);
                s->push_back(p4);

                s->push_back(p1);
                s->push_back(p3);
                s->push_back(p4);
            }
        }
    }
}

Point * bezierValue(float u, Point * p0,Point * p1,Point * p2,Point * p3){
    float b0 = (1.0 - u) * (1.0 - u) * (1.0 - u);
    float b1 = 3.0 * u * (1.0 - u) * (1.0 - u);
    float b2 = 3 * u * u * (1.0 - u);
    float b3 = u * u * u;

    float x = p0->getX()*b0 + p1->getX()*b1 + p2->getX()*b2 +  p3->getX()*b3;
    float y = p0->getY()*b0 + p1->getY()*b1 + p2->getY()*b2 +  p3->getY()*b3;
    float z = p0->getZ()*b0 + p1->getZ()*b1 + p2->getZ()*b2 +  p3->getZ()*b3;

    return new Point(x,y,z);
}

Point * bezierPatch(float u, float v,Patch * patch){
    Point * u_points [4];
    Point * v_points [4];

    int j = 0, k = 0;

    for(int i = 0; i < 16; i++){
        Point * aux = patch->getPoint(i);
        u_points[j] = aux;
        j++;

        if (j % 4 == 0){
            v_points[k++] = bezierValue(u,u_points[0],u_points[1],u_points[2],u_points[3]);

            j = 0;
        }
    }

    Point * res = bezierValue(v,v_points[0],v_points[1],v_points[2],v_points[3]);

    return res;
}





