#pragma once
#include "Batiment.h"
#include "BatimentPlace.h"

#include <vector>

using namespace std;

class Carte																																						//Un objet "Carte" est un objet possèdant une matrice (vecteur de vecteurs) permettant sa représentation
																																											//grâce aux batiments (nombres de l'objet "Batiment") qui les constituent, une liste d'objet "Batiment"
																																											//rescencant chaque batiment qui peut être placé sur celle-ci ainsi qu'une liste d'objet "BatimentPlace"
																																											//rescencant chaque batiment qui a été placé sur celle-ci.
{
private:
	vector<vector<int>>						schema;
	vector<Batiment>							listeBatiments;																				//Liste d'objets "Batiments" plaçables sur la carte (provenant de la lecture du fichier en question)
	vector<BatimentPlace>					listeBatimentsPlaces;																	//Liste d'objets "BatimentPlace" placés sur la carte (provenant de la liste ci-dessus)
	vector<pair<Batiment, float>>	listeCoeffResidentiel;																//Liste des coefficients de chaque batiment pour mesurer leur utilité
	vector<pair<Batiment, float>>	listeCoeffUtilitaire;																	//Liste des coefficients de chaque batiment pour mesurer leur utilité

	vector<Batiment>							listeUtilitaire;																			//Liste des Batiments Utilitaires disponibles
	vector<vector<Batiment>>			listeBatimentUtilitaireTriee;													//Liste des Batiments Utilitaires triée
	int 													hauteur;																							//Hauteur de la Carte
	int 													largeur;																							//Largeur de la Carte
	int 													walkDis;																							//Distance de marche de la Carte

public:
	Carte();																																						//Constructeur par défaut
	Carte(int h, int l, int wD);																												//Constructeur
	Carte(const Carte &);																																//Constructeur de recopie
	~Carte();																																						//Destructeur par défaut

	void 													toString();																						//Affichage de la Carte
	void 													toFile(string nom_fichier);														//Ecriture de la Carte
	void 													toOut(string nom_fichier);														//Fichier de sortie

	vector<Batiment>							getListeBatiments();																	//Getter de listeBatiments
	vector<BatimentPlace>					getListeBatimentsPlaces();														//Getter de listeBatimentsPlaces

	void													setListeBatiments(vector<Batiment> lBatiments);				//Setter de listeBatiments

	void													ajouterLignes();																			//Premet d'ajouter la ligne correspondante à tous les Batiments de listeBatiments
	void													ajouterBatimentPlace(BatimentPlace bp);								//Permet d'ajouter un objet "BatimentPlace" à la listeBatimentsPlaces

	bool													placerBatiment(Batiment b, pair<int, int> coord);			//Permet de placer un objet "Batiment" à une certaine coordonnée sur la carte.
																																											//Ajoute automatique un objet "BatimentPlace" à la listeBatimentsPlaces en fonction
																																											//en fonction de l'objet "Batiment" passé en argument.
	bool													placerResidentiel();																	//Permet de placer des Bâtiments Residentiels se trouvant dans listeCoeffResidentiel
	void													placerUtilitaire();																		//Permet de placer des Bâtiments Residentiels se trouvant dans listeCoeffUtilitaire

	void													calculCoeff(vector<Batiment> a);											//Calcul le score que pourrait rapporter chaque batiment.
	void													afficherBatCoeff();																		//Permet d'afficher les coefficients de rentabilités des Bâtiments dans listeCoeffResidentiel
	void													triBatimentRes();																			//Permet de trier les Batiments Residentiels par ordre décroissant de rentabilité
	void													triBatimentUti();																			//Permet de trier les Batiments Utilitaires par type et par taille

	int														calculLargMax();																			//Permet de calculer la largeur maximale des Batiments Utilitaires
	int														calculHautMax();																			//Permet de calculer la hauteur maxumale des Batiments Utilitaires
};
