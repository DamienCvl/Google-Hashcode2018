#include "map.hpp"
#include "scoreCalculator.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;
namespace fs = std::filesystem;
int main(int argc, char const *argv[])
{
    if (argc == 4)
    {

        ofstream csvOutput(argv[3]);

        csvOutput << "FichierEntree , Programme , TempsExecution , Score" << endl;
        for (const auto &entryInput : fs::directory_iterator(argv[2]))
        {
            //Creation d'un objet info qui contient le données pour un fichier d'entrée.
            InputInformation infos = InputReader ::readInputFile(entryInput.path().c_str());

            for (const auto &entryExec : fs::directory_iterator(argv[1]))
            {
                // create a string, i.e. an array  of 50 char
                char command[50];

                sprintf(command, "%s %s %s", entryExec.path().c_str(), entryInput.path().c_str(), "./output.out");

                auto start = std::chrono::high_resolution_clock::now();

                system(command);

                auto finish = std::chrono::high_resolution_clock::now();

                auto duree = finish - start;

                //Map m("./output.out", infos);

                //csvOutput << entryInput.path().c_str() << " , " << entryExec.path().c_str() << " , " << duree.count() << " , " << calculateScoreFromMap(m) << endl;
                csvOutput << entryInput.path().c_str() << " , " << entryExec.path().c_str() << " , " << duree.count() << " , " << 2000 << endl;
            }
        }
        return 0;
    }
    else
    {
        cout << "Il n'y a pas assez d'arguments" << endl;
        cout << "Arbitre RepertoireExecutable RepertoireFichiersCarte FichierDeSortie" << endl;
        return 0;
    }
}
