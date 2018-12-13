#include "Batiment.hpp"
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
};

class InputReader
{
public:
  static InputInformation readInputFile(const char *filePath);
  //static InputInformation readInputFile(ifstream &f);
  static Batiment readBatimentHeaderLine(char *line);
  static vector<int> getIndexCharOnLine(char c, char *line);
};
