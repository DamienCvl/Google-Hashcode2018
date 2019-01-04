#pragma once
#include <vector>

using namespace std;

class Batiment
{
	private:
	  int						specificite;							//Capacité Residentielle ou Type Utilitaire
	  int						hauteur;
	  int						largeur;

	  vector<pair<int, int>>	briques;								//Vecteur constitué uniquement des briques (un # dans le fichier) du batiment

	public:
	  Batiment();														//Constructeur par défaut
	  Batiment(const int spe, const int haut, const int larg);			//Constructeur
	  Batiment(const Batiment &);										//Constructeur de recopie
	  ~Batiment();														//Destructeur par défaut

	  Batiment operator=(const Batiment &b);							//Operateur d'affectation

	  virtual void				ajouterBrique(pair<int, int>);			//Ajoute un # du fichier de lecture

	  virtual void				toString();								//Affichage du batiment

	  int						getSpecificite() const;
	  int						getLargeur();
	  int						getHauteur();

	  vector<pair<int, int>>	getBriques() const;
};