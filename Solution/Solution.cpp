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
	
	Frecherche = FindFirstFile(".\\Maps\\*.in", &Fichier);
	if (Frecherche != INVALID_HANDLE_VALUE)
	{
		do {
			string nom_fichier = Fichier.cFileName;
			nom_fichier = nom_fichier.substr(0, nom_fichier.size() - 3);
			string chemin = ".\\Maps\\" + nom_fichier;
			cout << "Debut du traitement pour la carte : " << chemin.c_str() << endl;
			cout << "Lecture du fichier .in" << endl;
			InputInformation infos = InputReader::readInputFile((chemin + ".in").c_str());
			Carte carte(infos.getHauteur(), infos.getLargeur(), infos.getWalkingDist());

			carte.setListeBatiments(infos.getBatimentsUtilisables());
			carte.calculCoeff(carte.getListeBatiments());

			cout << "Placement des batiments residentiels..." << endl;
			carte.placerResidentiel();
			cout << "Placement des batiments utilitaires..." << endl;
			carte.placerUtilitaire();

			cout << "Creation de la carte de visualisation " << chemin + ".visu ..." << endl;
			carte.toFile(chemin);															//Creation de la map visuel (.visu)
			cout << "Creation du fichier de sortie " << chemin + ".out ..." << endl << endl;
			carte.toOut(chemin);															//Creation de la fichier de sortie (.out)

		} while (FindNextFile(Frecherche, &Fichier));
	}
	
	return 0;
}