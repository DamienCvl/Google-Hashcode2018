#include "map.hpp"
#include "scoreCalculator.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

int main(int argc, const char *argv[])
{
    InputInformation infos = InputReader ::readInputFile(argv[1]);
    Map m(argv[2], infos);
    cout << calculateScoreFromMap(m) << endl;
}