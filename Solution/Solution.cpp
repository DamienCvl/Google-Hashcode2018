#pragma once
#include <iostream>
#include <fstream>

#include "Carte.h"
#include "InputReader.hpp"

using namespace std;

int main() {

	InputInformation infos = InputReader::readInputFile("../Maps/b_short_walk.in");

	cout << "\n" << "Affichage des batiments de la fonction de DEMS : " << endl;

	for (int i = 0; i < infos.getBatimentsUtilisables().size(); i++)
	{
		Batiment btmp = infos.getBatimentAt(i);
		btmp.toString();
	}

	Carte carte(infos.getLargeur());

	carte.placerBatiment(infos.getBatimentAt(1), pair<int, int>(0, 0));
	carte.placerBatiment(infos.getBatimentAt(3), pair<int, int>(0, 3));

	carte.toFile();

	return 0;
}