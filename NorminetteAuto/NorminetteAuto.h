#pragma once

#include <ctime>
#include "../Header.h"
#include "../FileEditor/FileEditor.h"
#include "../FileTextEditor/FileTextEditor.h"
#include "../NorminetteCorrector/NorminetteCorrector.h"

namespace     NorminetteAuto
{
    //NorminetteCorrector file;

    //void initFile();

    void CorrectFile(std::string filename);
    void CorrectFilesInFile(std::string filename);
    
    //void print();
    //void clear();
}

namespace CalculateWorkTime
{
    void CorrectFile(std::string filename);
}