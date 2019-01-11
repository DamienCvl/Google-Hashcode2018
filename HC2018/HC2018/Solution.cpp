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
			string chemin = "..\\Maps\\" + nom_fichier;
			cout << "Chemin : " << chemin.c_str() << endl;
			InputInformation infos = InputReader::readInputFile((chemin + ".in").c_str());
			Carte carte(infos.getHauteur());

			carte.setListeBatiments(infos.getBatimentsUtilisables());
			carte.calculCoeff(carte.getListeBatiments());

			carte.placerResidentiel();
			carte.placerUtilitaire();

			carte.toFile(nom_fichier);
			carte.toOut(nom_fichier);
			//InputInformation infos = InputReader::readInputFile("..\\Maps\\d_wide_selection.in");
			Map m1((chemin + ".out").c_str(), infos);
			std::cout << calculateScoreFromMap(m1) << std::endl;

		} while (FindNextFile(Frecherche, &Fichier));
	}
	//SCORES :
	//MAP A : 25
	//MAP B : 2.332.499
	//MAP C : 5.375.123
	//MAP D : 2.770.052
	//MAP E : 1.013.540
	//MAP F : 
	return 0;
}