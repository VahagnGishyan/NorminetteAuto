#pragma once
#include "FileEditor.h"
class NorminetteCorrector : public FileEditor
{
private:
    //Assistants
    ushint                          m_startLine;
    //std::vector<unsigned short>     m_PreprocessorIndex;
    std::vector<std::vector<short>> m_BracesIndex;
    //std::vector<bool>               m_ErrorStatusRegister;
public:
    //initialization 
    NorminetteCorrector();
    NorminetteCorrector(std::string filename);

    //For corrector
    void correctAll(); 

public:
    // heto dardznel mi masy private
    
    //Block 1, basic check
    bool chackBasic();
    bool preliminaryInspection();
    bool checkFormatHeading42();
    bool checkPreprocessor();

    //Block 1, basic check
    void preliminaryCorrectingFileFormat();
};


