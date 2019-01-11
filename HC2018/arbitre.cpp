#pragma once
#include "map.hpp"
#include "scoreCalculator.hpp"
#include <iostream>

int mainArbitre(int argc, char const *argv[])
{
    //InputInformation infos = InputReader ::readInputFile("/home/damien/Documents/cours/poly/4A/projetC++/inputs/a_example.in");
    //Map m1("/home/damien/Documents/cours/poly/4A/projetC++/outputs/13_a_example_2018-10-22T17_27_59.722707.out", infos);

    InputInformation infos = InputReader ::readInputFile("..\\Maps\\b_short_walk.in");
	//PROF MAP B : 2.175.522
    Map m1("..\\Maps\\b_short_walk.out", infos);

    //std::cout << m1 << std::endl;
    std::cout << calculateScoreFromMap(m1) << std::endl;

    return 0;
}
