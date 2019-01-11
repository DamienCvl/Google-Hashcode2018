#pragma once
#include "scoreCalculator.hpp"
#include "map.hpp"
#include <boost/functional/hash.hpp>
#include <chrono>
#include <exception>
#include <iostream>

void getOuterCoordonates(int x, int y, int dist, unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &resultSet)
{
    int index = 0;
    int xx = x - dist;
    int yy = y;
    vector<pair<int, int>> listCoordonates(4 * dist);
    for (int i = 1; i <= dist; i++)
    {
        listCoordonates[index] = pair<int, int>(xx + i, yy - i);
        index++;
    }
    xx = listCoordonates[index - 1].first;
    yy = listCoordonates[index - 1].second;
    for (int i = 1; i <= dist; i++)
    {
        listCoordonates[index] = pair<int, int>(xx + i, yy + i);
        index++;
    }
    xx = listCoordonates[index - 1].first;
    yy = listCoordonates[index - 1].second;
    for (int i = 1; i <= dist; i++)
    {
        listCoordonates[index] = pair<int, int>(xx - i, yy + i);
        index++;
    }
    xx = listCoordonates[index - 1].first;
    yy = listCoordonates[index - 1].second;
    for (int i = 1; i <= dist; i++)
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
    for (auto &elem : m.getBtmResidentiels())
    {
        unordered_set<pair<int, int>, boost::hash<pair<int, int>>> cells;
        getAllCoordonatesOfBuilding(elem.getCoordonnees().first, elem.getCoordonnees().second, m.getDist(), elem.GetBriques(), cells);
        score = score - (elem.getSpecificite() * calculateScoreFromSet(cells, m.getMatrice(), m.getHauteur(), m.getLargeur()));
    }
    return score;
}

int calculateScoreFromFiles(const char *subimissionFile, const char *inputFile)
{
    const InputInformation info = InputReader::readInputFile(inputFile);
    Map map(subimissionFile, info);
    return calculateScoreFromMap(map);
}
