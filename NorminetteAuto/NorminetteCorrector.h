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
    NorminetteCorrector() : FileEditor(), m_startLine(0)
    {

    }
    NorminetteCorrector(std::string filename) : FileEditor(filename), m_startLine(12)
    {

    }

    //for work
    int searchSymbolsInLine(const std::string& line, const std::string& symbols);
    int searchSymbolsInLineIndex(int index, const std::string& symbols);
    void divideLineIntoThreeNewLines(int indexLine, int indexLeft, int indexRight);

    //For corrector
    void correctAll(); 

public:
    // heto dardznel mi masy private
    
    //Block 1, basic check
    bool chackBasic();
    bool preliminaryInspection();
    bool checkFormatHeading42();
    bool checkPreprocessor();

    //Block 2, Preliminary Correcting File Format
    void preliminaryCorrectingFileFormat();
    void bracesMustBeOnNewLine();
    //void correctSemicolon();
    void afterSemicolonMustBeEmpty();
    void unnecessarySpaces();
    void deleteBlankLines();

    //Block 3, correct Inside Line
    void correctInsideLine();
    void separateByKeySymbols(std::vector<std::string>& data);
    //key symbols, " ", (), [], =, +, ...

    void correctTabulations();
};


