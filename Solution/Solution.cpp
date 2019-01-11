#pragma once
#include <iostream>
#include <fstream>

#include "Carte.h"
#include "InputReader.hpp"
#include "scoreCalculator.hpp"


using namespace std;

int main() {
	/*InputInformation infos = InputReader::readInputFile("..\\Maps\\b_short_walk.in");
	Carte carte(infos.getHauteur());

	carte.setListeBatiments(infos.getBatimentsUtilisables());
	carte.calculCoeff(carte.getListeBatiments());

	carte.placerBatimentOpti();
	carte.placerUtilitaire();

	//carte.toFile();
	carte.toOut();*/
	calculateScoreFromFiles("..\\Maps\\b_short_walk.out", "..\\Maps\\b_short_walk.in");
	return 0;
}