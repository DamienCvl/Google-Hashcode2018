#pragma once
#include "../Solution/InputReader.hpp"
//#include <boost/functional/hash.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Map
{
  private:
    int hauteur;
    int largeur;
    int nbBatimentIndique;
    int nbBatimentReel;
    int dist;

    vector<vector<int>> matrice;
    vector<BatimentPlace> btmResidentiels;

  public:
    Map(const char *filename, const InputInformation &info)
    {
        hauteur = info.getHauteur();
        largeur = info.getLargeur();
        dist = info.getWalkingDist();
        nbBatimentReel = 0;

        ifstream submisionFile;
        submisionFile.open(filename, ifstream::in);

        btmResidentiels = vector<BatimentPlace>();
        matrice = vector<vector<int>>(hauteur);
        for (int i = 0; i < hauteur; i++)
        {
            matrice[i] = vector<int>(largeur, 0);
        }

        if (!submisionFile)
        {
            cout << "Le fichier de solution n'a pas pu être ouvert !" << endl;
        }
        else
        {
            char line[100];
            submisionFile.getline(line, 100);

            char *tok = strtok(line, " ");
            nbBatimentIndique = stoi(tok);

            while (submisionFile.getline(line, 100))
            {
                tok = strtok(line, " ");
                int buildingID = stoi(tok);

                tok = strtok(NULL, " ");
                int buildingX = stoi(tok);

                tok = strtok(NULL, " ");
                int buildingY = stoi(tok);

                Batiment b = info.getBatimentAt(buildingID);
                if (!placeBuildingAt(buildingX, buildingY, b.getSpecificite(), b.getBriques()))
                {
                    cout << "Il y a une erreur dans le fichier à la ligne " << nbBatimentReel << endl;
                    throw(exception());
                }
                if (b.getSpecificite() < 0)
                {
                    btmResidentiels.insert(btmResidentiels.end(), BatimentPlace(info.getBatimentPointerAt(buildingID), buildingX, buildingY));
                }
            }
        }
        submisionFile.close();
        if (nbBatimentIndique != nbBatimentReel)
        {
            cout << "Il y a une erreur le nombre de buildings indiqué ne correspond pas au nombre de buildings placés" << endl;
        }
    }
    Map(int l, int h, int nbBat)
    {
        hauteur = h;
        largeur = l;
        nbBatimentIndique = nbBat;
        nbBatimentReel = 0;
        vector<vector<int>> matrice(hauteur);
        for (int i = 0; i < hauteur; i++)
        {
            matrice[i] = vector<int>(largeur, 0);
        }
    }
    ~Map();
    bool placeBuildingAt(int x, int y, int buildingValue, const vector<pair<int, int>> &buildingScheme);
    friend ostream &operator<<(ostream &o, const Map &m);

    vector<BatimentPlace> getBtmResidentiels() const { return btmResidentiels; }
    inline vector<vector<int>> getMatrice() const { return matrice; }
    inline const int getDist() const { return dist; }
    inline const int getHauteur() const { return hauteur; }
    inline const int getLargeur() const { return largeur; }
    static int getScore(const char *, const char *);
};