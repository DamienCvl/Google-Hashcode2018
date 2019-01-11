#pragma once
#include <iostream>

#include "BatimentPlace.h"

BatimentPlace::BatimentPlace(Batiment bat, pair<int, int> coord)
{
	batiment = bat;
	coordonnees = coord;
}

pair<int, int> BatimentPlace::getCoordonnees()
{
	return this->coordonnees;
}

void BatimentPlace::setCoordonnees(pair<int, int> coord)
{
	this->coordonnees = coord;
}

Batiment BatimentPlace::getBatiment()
{
	return batiment;
}
