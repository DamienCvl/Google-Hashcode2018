#include "BatimentPlace.h"
#include "Batiment.h"
#include <vector>

class InputInformation
{
private:
  std::vector<Batiment> batimentsUtilisable;
  int hauteur;
  int largeur;
  int walkingDist;

public:
  InputInformation(int h, int l, int wd, int nbBatiments);
  void addBatiment(Batiment b);
  inline const int getHauteur() const { return hauteur; };
  inline const int getLargeur() const { return largeur; };
  inline const int getWalkingDist() const { return walkingDist; };
  const Batiment getBatimentAt(int index) const { return batimentsUtilisable[index]; }
  const Batiment *getBatimentPointerAt(int index) const { return &batimentsUtilisable[index]; }

  //Hugo
  std::vector<Batiment> getBatimentsUtilisables() { return batimentsUtilisable; };
};

class InputReader
{
public:
  static InputInformation readInputFile(const char *filePath);
  static Batiment readBatimentHeaderLine(char *line);
  static vector<int> getIndexCharOnLine(char c, char *line);
};
