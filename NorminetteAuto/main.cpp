#include "NorminetteCorrector.h"

int main()
{
    std::cout << "Start work main.cpp" << std::endl << std::endl;

    NorminetteCorrector object("data.txt");
    //object.print();



    object.correctAll();

    object.updateFile("newData.txt");

    std::cout << std::endl << "End work main.cpp" << std::endl;

    return 0;
}