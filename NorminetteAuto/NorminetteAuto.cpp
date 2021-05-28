#include "NorminetteAuto.h"

#include <ctime>

void NorminetteAuto::CorrectFile(std::string filename)
{
    NorminetteCorrector data(filename);
    data.correctAll();
}


void CalculateWorkTime::CorrectFile(std::string filename)
{
    std::vector<ulong> time;
    ushint cycle = 100;
    std::cout << "Start Work" << std::endl;

    for (ushint index = 0; index < cycle; ++index)
    {
	ulong startTime = clock();
	NorminetteAuto::CorrectFile(filename);
	ulong endTime = clock();

	time.push_back(endTime - startTime);
    }

    ulong sum = 0;
    for (ushint index = 0; index < cycle; ++index)
    {
	sum += time[index];
    }
    sum /= cycle;
    std::cout << "time = " << sum << std::endl;
}
