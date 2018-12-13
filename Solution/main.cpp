#include "InputReader.hpp"
#include <fstream>
#include <iostream>

main(int argc, char const *argv[])
{
    /*
    ifstream f;
    f.open("/home/damien/Documents/cours/poly/4A/projetC++/hashcode-2018/Solution/hello", fstream::in);
    char line[100];
    f.getline(line, 100);
    cout << line << endl;
    f.close();
    */

    InputInformation infos = InputReader ::readInputFile("/home/damien/Documents/cours/poly/4A/projetC++/hashcode-2018/Solution/hello");
    return 0;
}
