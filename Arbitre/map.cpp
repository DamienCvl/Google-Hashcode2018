#pragma once
#include "map.hpp"
#include "../Solution/Batiment.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

bool Map ::placeBuildingAt(int x, int y, int buildingValue, const vector<pair<int, int>> &buildingScheme)
{
    for (auto it = buildingScheme.begin(); it < buildingScheme.end(); ++it)
    {
        int xx = x + (*it).first;
        int yy = y + (*it).second;

        if (matrice[xx][yy] == 0)
        {
            matrice[xx][yy] = buildingValue;
        }
        else
        {
            return false;
        }
    }
    nbBatimentReel++;
    return true;
}

Map ::~Map()
{
    //faire le destructeur
}
ostream &operator<<(ostream &o, const Map &m)
{
    for (auto itx = m.matrice.begin(); itx != m.matrice.end(); ++itx)
    {
        for (auto ity = (*itx).begin(); ity != (*itx).end(); ++ity)
        {
            o << (*ity) << " ";
        }
        o << '\n';
    }
    return o;
}

/*
int main(int argc, char const *argv[])
{
    vector<pair<int, int>> b1 = {pair<int, int>(0, 0),
                                 pair<int, int>(0, 1),
                                 pair<int, int>(1, 1),
                                 pair<int, int>(1, 2),
                                 pair<int, int>(2, 2)};

    vector<pair<int, int>> b2 = {pair<int, int>(0, 0),
                                 pair<int, int>(0, 1),
                                 pair<int, int>(0, 2),
                                 pair<int, int>(0, 3)};

    vector<pair<int, int>> b3 = {pair<int, int>(0, 0),
                                 pair<int, int>(0, 1),
                                 pair<int, int>(0, 2),
                                 pair<int, int>(1, 0),
                                 pair<int, int>(1, 1),
                                 pair<int, int>(1, 2)};

    vector<vector<pair<int, int>>> buildingScheme = {b1, b2, b3};

    Map("./submisionFile.txt", buildingScheme, 100, 30;

    ofstream outputFile("./resultFile.txt");
    outputFile << map << endl;
    return 0;
}
    */
