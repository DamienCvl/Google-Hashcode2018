#include<iostream>
#include<vector>
#include<fstream>
#include<regex>
#include<string>
#include<exception>

using namespace std;

bool placeBuildingAt(int x, int y, int buildingValue, const vector<pair<int, int>> &buildingScheme, vector<vector<int>> &map);

ostream& operator<<(ostream &o, const vector<vector<int>> &m){
    for (auto itx = m.begin(); itx != m.end(); ++itx){
        for (auto ity = (*itx).begin(); ity != (*itx).end(); ++ity){
            o << (*ity) << " ";
        }
        o << '\n';
    }
    /*
    for (int x = 0; x < m.size(); x++){
        for (int y  = 0; m[x].size(); y++) {
            o << m[x][y] << " ";
        }
        o << "\n";
    }
    */
    return o;
}


vector<vector<int>> createSubmisionMap(const char* filename, vector<vector<pair<int,int>>> buildingScheme, int dimX, int dimY){
    ifstream submisionFile;
    submisionFile.open(filename, ifstream::in);
    int countBuilding = 0;

    vector<vector<int>> map(dimX);
    for(int i = 0; i < dimX; i++){
        map[i] = vector<int>(dimY, 0);
    }

    if(!submisionFile){
        cout << "Le fichier de solution n'a pas pu être ouvert !" << endl;
    }
    else{
        char line[100];
        submisionFile.getline(line, 100);
        
        char *tok = strtok(line, " ");
        int numberOfBuildings = stoi(tok);

        while(submisionFile.getline(line, 100)){
            tok = strtok(line, " ");
            int buildingID =  stoi(tok);

            tok = strtok(NULL, " ");
            int buildingX = stoi(tok);

            tok = strtok(NULL, " ");
            int buildingY = stoi(tok);

            countBuilding++;
            cout << buildingID << " " << buildingX << " " << buildingY << endl;

            if(!placeBuildingAt(buildingX, buildingY, 1, buildingScheme[buildingID], map)){
                cout << "Il y a une erreur dans le fichier à la ligne " << countBuilding << endl;
                throw(exception());
            }
        }
    }
    submisionFile.close();
    return map;
}

bool placeBuildingAt(int x, int y, int buildingValue, const vector<pair<int, int>> &buildingScheme, vector<vector<int>> &map){
    for(auto it = buildingScheme.begin(); it < buildingScheme.end(); ++it){
        int xx = x + (*it).first;
        int yy = y + (*it).second;

        if(map[xx][yy] == 0){
            map[xx][yy] = buildingValue;
        }
        else{
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    vector<pair<int, int>> b1 = {pair<int, int>(0,0),
                                 pair<int, int>(0,1),
                                 pair<int, int>(1,1),
                                 pair<int, int>(1,2),
                                 pair<int, int>(2,2)};

    vector<pair<int, int>> b2 = {pair<int, int>(0,0),
                                 pair<int, int>(0,1),
                                 pair<int, int>(0,2),
                                 pair<int, int>(0,3)};

    vector<pair<int, int>> b3 = {pair<int, int>(0,0),
                                 pair<int, int>(0,1),
                                 pair<int, int>(0,2),
                                 pair<int, int>(1,0),
                                 pair<int, int>(1,1),
                                 pair<int, int>(1,2)};

    vector<vector<pair<int,int>>> buildingScheme = {b1,b2,b3};

    auto map = createSubmisionMap("./submisionFile.txt", buildingScheme, 100, 30);

    ofstream outputFile("./resultFile.txt");
    outputFile << map << endl;
    return 0;
}
