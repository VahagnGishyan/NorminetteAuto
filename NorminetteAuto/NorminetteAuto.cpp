
#include "NorminetteAuto.h"

void NorminetteAuto::CorrectFile(std::string filename)
{
    NorminetteCorrector data(filename);
    data.print();
    data.correctAll();
    data.print();
    data.clear();
}
void NorminetteAuto::CorrectFilesInFile(std::string filename)
{
    FileEditor file(filename);

    for(ushint index = 0; index < file.size(); ++index)
    {
        std::cout<<"index = " <<index << std::endl;
        std::cout<<"filename = " <<file.getLine(index)<<std::endl;
        NorminetteAuto::CorrectFile("../Data/" + file.getLine(index));
    }
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

/*
    m_fileName = fileName;
    std::ifstream dataFileForInput(m_fileName);
    if (!dataFileForInput)
    {
        std::cout << "Error, FileEditor.cpp, dataFileForInput.open() == false" << std::endl;
        std::cout << "fileName = " << m_fileName << std::endl;
    }
    else
    {
        while (!dataFileForInput.eof())
        {
            std::string line;
            getline(dataFileForInput, line);
            addNewLineBack(line);
        }
    }
    dataFileForInput.close();
    */