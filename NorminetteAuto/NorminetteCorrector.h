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
    std::vector<std::string> separateByKeySymbols(ushint lineStart);
    //key symbols, " ", (), [], =, +, ...
    bool searchInWords(const std::vector<std::string>& words, const std::string& keyWord);
    //return true if found
    void addNewLineInTextIndex(const unsigned short indexLine, std::vector< std::vector<std::string>>& text, const std::vector<std::string>& newLine);
    void deleteLineInTextIndex(const unsigned short indexLine, std::vector< std::vector<std::string>>& text);

    void correctSemicolon(ushint& start, std::vector< std::vector<std::string>>& text);
    void aloneSemicolonRaiseUp(ushint& start, std::vector< std::vector<std::string>>& words);
    void deleteUnnecessarySemicolon(ushint& indexLine, std::vector< std::vector<std::string>>& text);
    void beforeSemicolonShouldBeNoSpace(ushint& start, std::vector< std::vector<std::string>>& words);

    void correctIfWhile(ushint& start, std::vector< std::vector<std::string>>& words);
    void correctIf(ushint& indexLine, std::vector< std::vector<std::string>>& words);
    void correctWhile(ushint& indexLine, std::vector< std::vector<std::string>>& words);

    void correctReturns(std::vector<std::string>& line);



    void correctTabulations();
};


