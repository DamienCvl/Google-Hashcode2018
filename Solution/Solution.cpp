#pragma once
#include <iostream>
#include <fstream>

#include "Carte.h"
#include "InputReader.hpp"

using namespace std;

int main() {

	InputInformation infos = InputReader::readInputFile("../Maps/b_short_walk.in");

	cout << "\n" << "Affichage des batiments de la fonction de DEMS : " << endl;

	/*for (unsigned int i = 0; i < infos.getBatimentsUtilisables().size(); i++)
	{
		Batiment btmp = infos.getBatimentAt(i);
		btmp.toString();
	}*/

	Carte carte(infos.getLargeur());

	carte.calculCoeff(infos.getBatimentsUtilisables());
	carte.setListeBatiments(infos.getBatimentsUtilisables());
	carte.placerBatimentOpti();
	
	carte.placerUtilitaire();

	//carte.toOut();

	return 0;
}