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
    const char *inputFile = "fileinput";
    const char *outputFile = "fileouput";

    for (const auto &entry : fs::directory_iterator(argv[1]))
    {
        // create a string, i.e. an array  of 50 char
        char command[50];

        sprintf(command, "%s %s %s", entry.path().c_str(), inputFile, outputFile);

        //cout << command << endl;
        system(command);
    }
    return 0;
}