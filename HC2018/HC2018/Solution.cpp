#pragma once
#include <iostream>
#include <fstream>
#include <windows.h> 

#include "Carte.h"
#include "InputReader.hpp"
#include "scoreCalculator.hpp"


using namespace std;

int main() {

	WIN32_FIND_DATA Fichier;
	HANDLE Frecherche;

	Frecherche = FindFirstFile("..\\Maps\\*.in", &Fichier);
	if (Frecherche != INVALID_HANDLE_VALUE)
	{
		do {
			string nom_fichier = Fichier.cFileName;
			nom_fichier = nom_fichier.substr(0, nom_fichier.size() - 3);
			string chemin = "..\\Maps\\" + nom_fichier + ".in";
			cout << "Chemin : " << chemin.c_str() << endl;
			InputInformation infos = InputReader::readInputFile(chemin.c_str());
			Carte carte(infos.getHauteur());

			carte.setListeBatiments(infos.getBatimentsUtilisables());
			carte.calculCoeff(carte.getListeBatiments());

			carte.placerResidentiel();
			carte.placerUtilitaire();

			//carte.toFile();
			carte.toOut(nom_fichier);
			Map m1("..\\Maps\\b_short_walk.out", infos);
			std::cout << calculateScoreFromMap(m1) << std::endl;

		} while (FindNextFile(Frecherche, &Fichier));
	}
	return 0;
}