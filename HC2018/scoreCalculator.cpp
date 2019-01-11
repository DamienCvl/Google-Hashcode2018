#pragma once
#include "scoreCalculator.hpp"
#include "map.hpp"
#include "InputReader.hpp"
#include <boost/functional/hash.hpp>
#include <chrono>
#include <exception>
#include <iostream>

void getOuterCoordonates(int x, int y, int dist, unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &resultSet)
{
    int index = 0;
    int xx = x - dist;
    int yy = y;
    vector<pair<int, int>> listCoordonates(5 * dist);
    for (int i = 1; i < dist + 1; i++)
    {
        listCoordonates[index] = pair<int, int>(xx + i, yy - i);
        index++;
    }
    xx = listCoordonates[index - 1].first;
    yy = listCoordonates[index - 1].second;
    for (int i = 1; i < dist + 1; i++)
    {
        listCoordonates[index] = pair<int, int>(xx + i, yy + i);
        index++;
    }
    xx = listCoordonates[index - 1].first;
    yy = listCoordonates[index - 1].second;
    for (int i = 1; i < dist + 1; i++)
    {
        listCoordonates[index] = pair<int, int>(xx - i, yy + i);
        index++;
    }
    xx = listCoordonates[index - 1].first;
    yy = listCoordonates[index - 1].second;
    for (int i = 1; i < dist + 1; i++)
    {
        listCoordonates[index] = pair<int, int>(xx - i, yy - i);
        index++;
    }
    resultSet.insert(listCoordonates.begin(), listCoordonates.end());
}
void getAllCoordonates(int x, int y, int dist, unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &resultSet)
{
    for (int d = dist; d > 0; d--)
    {
        getOuterCoordonates(x, y, d, resultSet);
    }
    resultSet.insert(pair<int, int>(x, y));
}
void getAllCoordonatesOfBuilding(int x, int y, int dist, const vector<pair<int, int>> &buildingScheme, unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &resultSet)
{
    for (auto it = buildingScheme.begin(); it != buildingScheme.end(); ++it)
    {
        getAllCoordonates((*it).first + x, (*it).second + y, dist, resultSet);
    }
}
int calculateScoreFromSet(const unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &set, const vector<vector<int>> &map, int hauteur, int largeur)
{
    int score = 0;
    unordered_set<int> typeOfBuildingAlreadyCovered;
    /*
    for (auto it = set.begin(); it != set.end(); ++it)
    {
        try
        {
            if ((*it).first >= 0 and (*it).second >= 0 and (*it).first < hauteur and (*it).second < largeur)
            {
                int valuePoint = map[(*it).first][(*it).second];
                if (valuePoint > 0 and typeOfBuildingAlreadyCovered.count(valuePoint) == 0)
                {
                    score++;
                    typeOfBuildingAlreadyCovered.insert(valuePoint);
                }
            }
            else
            {
                ++it;
            }
        }
        //L'élément n'existe pas dans la carte, index out of bound on ne le traite donc pas.
        catch (exception e)
        {
            ++it;
        }
    }
    */
    for (const auto &elem : set)
    {
        try
        {
            if (elem.first >= 0 and elem.second >= 0 and elem.first < hauteur and elem.second < largeur)
            {
                int valuePoint = map[elem.first][elem.second];
                if (valuePoint > 0 and typeOfBuildingAlreadyCovered.count(valuePoint) == 0)
                {
                    score++;
                    typeOfBuildingAlreadyCovered.insert(valuePoint);
                }
            }
        }
        //L'élément n'existe pas dans la carte, index out of bound on ne le traite donc pas.
        catch (exception e)
        {
        }
    }
    return score;
}
int calculateScoreFromMap(const Map &m)
{
    int score = 0;
	int c = 0;
    for (auto elem : m.getBtmResidentiels())
    {
		cout << "Score : " << score << " - Boucle : " << c << "/" << m.getBtmResidentiels().size() << endl;
        unordered_set<pair<int, int>, boost::hash<pair<int, int>>> cells;
        getAllCoordonatesOfBuilding(elem.getCoordonnees().first, elem.getCoordonnees().second, m.getDist(), elem.getBatiment().getBriques(), cells);
        score = score - (elem.getBatiment().getSpecificite() * calculateScoreFromSet(cells, m.getMatrice(), m.getHauteur(), m.getLargeur()));
		c++;
    }
    /*
    for (int i = 0; i < 1000; i++)
    {
        unordered_set<pair<int, int>, boost::hash<pair<int, int>>> cells;
        getAllCoordonatesOfBuilding(m.getBtmResidentiels()[i].getCoordonnees().first, m.getBtmResidentiels()[i].getCoordonnees().second, m.getDist(), m.getBtmResidentiels()[i].GetBriques(), cells);
        score = score - (m.getBtmResidentiels()[i].getSpecificite() * calculateScoreFromSet(cells, m.getMatrice(), m.getHauteur(), m.getLargeur()));
    }
    */
    /*
    for (auto it = m.getBtmResidentiels().begin(); it < m.getBtmResidentiels().end(); ++it)
    {
        unordered_set<pair<int, int>, boost::hash<pair<int, int>>> cells;
        getAllCoordonatesOfBuilding((*it).getCoordonnees().first, (*it).getCoordonnees().second, m.getDist(), (*it).GetBriques(), cells);
        score = score - ((*it).getSpecificite() * calculateScoreFromSet(cells, m.getMatrice(), m.getHauteur(), m.getLargeur()));
    }
    */
    return score;
}

int calculateScoreFromFiles(const char *subimissionFile, const char *inputFile)
{
    const InputInformation info = InputReader::readInputFile(inputFile);
    Map map(subimissionFile, info);
    return calculateScoreFromMap(map);
}

/*
int main(int argc, char const *argv[])
{
    unordered_set<pair<int, int>, boost::hash< pair<int,int>>> coordonateSet;
    getOuterCoordonates(4,4,3, coordonateSet);
    for (auto it = coordonateSet.begin(); it != coordonateSet.end(); ++it){
        cout << " " << (*it).first;
        cout << " " << (*it).second;
        cout << endl;
    }
    return 0;
auto start = chrono::high_resolution_clock::now();

for (int i = 0; i < 10000000; i++)
{

    vector<vector<int>> map(10);

    vector<int> l1 = {7,7,7,1,1,1,0,0};
    vector<int> l2 = {9,7,7,1,1,1,0,0};
    vector<int> l3 = {9,9,7,0,0,8,9,0};
    vector<int> l4 = {2,9,-10,-10,0,8,9,9};
    vector<int> l5 = {2,-10,-10,-10,0,8,0,9};
    vector<int> l6 = {2,3,3,3,8,8,0,0};
    vector<int> l7 = {2,3,3,3,0,0,0,0};

map[0] = {7, 7, 7, 1, 1, 1, 0, 0};
map[1] = {9, 7, 7, 1, 1, 1, 0, 0};
map[2] = {9, 9, 7, 0, 0, 8, 9, 0};
map[3] = {2, 9, -10, -10, 0, 8, 9, 9};
map[4] = {2, 0, -10, -10, 0, 8, 0, 9};
map[5] = {2, 0, -10, -10, 8, 8, 0, 0};
map[6] = {2, 3, 3, 3, 8, 8, 0, 0};
map[7] = {2, 3, 3, 3, 0, 0, 0, 0};

vector<pair<int, int>> scheme = {pair<int, int>(0, 0),
                                 pair<int, int>(1, 0),
                                 pair<int, int>(0, 1),
                                 pair<int, int>(1, 1),
                                 pair<int, int>(2, 0),
                                 pair<int, int>(2, 1)};

unordered_set<pair<int, int>, boost::hash<pair<int, int>>> cells;
getAllCoordonatesOfBuilding(2, 3, 3, scheme, cells);
int score = calculateScoreFromSet(cells, map);
}

auto end = chrono::high_resolution_clock::now();
auto elapsed = end - start;
cout << elapsed.count() << endl;
}
*/
