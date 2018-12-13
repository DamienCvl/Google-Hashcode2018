#pragma once

#include "InputReader.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

InputInformation ::InputInformation(int h, int l, int wd, int nbBatiments)
{
    hauteur = h;
    largeur = l;
    walkingDist = wd;
    batimentsUtilisable = vector<Batiment>(0);
}

void InputInformation ::addBatiment(Batiment b)
{
    batimentsUtilisable.insert(batimentsUtilisable.end(), b);
}

//InputInformation InputReader::readInputFile(ifstream &f)
InputInformation InputReader::readInputFile(const char *filepath)
{
    ifstream f;
    f.open(filepath, fstream::in);
    if (!f)
    {
        throw(exception());
    }
    char line[100];
    f.getline(line, 100);
    char *tok = strtok(line, " ");
    int h = stoi(tok);

    tok = strtok(NULL, " ");
    int l = stoi(tok);

    tok = strtok(NULL, " ");
    int walkingDist = stoi(tok);

    tok = strtok(NULL, " ");
    int nbBatiments = stoi(tok);

    InputInformation inputInfo(h, l, walkingDist, nbBatiments);

    //pensez à mettre le code suivant dans une fonction plutôt

    while (f.getline(line, 100))
    {

        Batiment b = InputReader::readBatimentHeaderLine(line);

        for (int i = 0; i < b.getHauteur(); i++)
        {
            f.getline(line, 100);
            vector<int> indexBriqueOnLine = InputReader::getIndexCharOnLine('#', line);
            for (auto it = indexBriqueOnLine.begin(); it < indexBriqueOnLine.end(); ++it)
            {
                //ajoute la brique de ligne i et de la collone (*it)
                b.ajouterBrique(pair<int, int>(i, (*it)));
            }
        }
        inputInfo.addBatiment(b);
    }
    return inputInfo;
}

Batiment InputReader ::readBatimentHeaderLine(char *line)
{
    char *tok = strtok(line, " ");

    bool residential = (*tok == 'R');

    tok = strtok(NULL, " ");
    int h = stoi(tok);

    tok = strtok(NULL, " ");
    int l = stoi(tok);

    tok = strtok(NULL, " ");

    /*Si le batiment est residentiel alors la spe
    représente la capacité pour la différencier d'un batiment
    utilitaire le nombre est négatif.
    */
    int spe;
    if (residential)
    {
        spe = -(strtol(tok, NULL, 10));
    }
    else
    {
        spe = strtol(tok, NULL, 10);
    }

    return Batiment(spe, h, l);
}

vector<int> InputReader ::getIndexCharOnLine(char c, char *line)
{
    vector<int> l(0);
    int index = 0;
    char currentChar = line[0];
    while (currentChar != '\0')
    {
        if (currentChar == c)
        {
            l.insert(l.end(), index);
        }
        index++;
        currentChar = line[index];
    }
    return l;
}