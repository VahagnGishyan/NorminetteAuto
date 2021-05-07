#pragma once
#include "FileEditor.h"
class NorminetteCorrector : public FileEditor
{
private:
    //Assistants
    ushint				    m_startLine;
    //std::vector<unsigned short>	    m_PreprocessorIndex;
    std::vector<std::vector<short>>	    m_BracesIndex;
    //std::vector<bool>			    m_ErrorStatusRegister;
    std::vector< std::vector<std::string>>  m_text;
    std::vector<std::string>		    m_varibleKeyWords;
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
    void createMemberText();
    std::vector<std::string> separateByKeySymbols(ushint lineStart);     //key symbols, " ", (), [], =, +, ...
    bool searchInWords(const std::vector<std::string>& words, const std::string& keyWord);    //return true if found
    void addNewLineInTextIndex(const unsigned short indexLine,  const std::vector<std::string>& newLine);
    void deleteLineInTextIndex(const unsigned short indexLine);
    void updataText();

    void correctSemicolon();
    void aloneSemicolonRaiseUp(ushint& start);
    void deleteUnnecessarySemicolon(ushint& indexLine);
    void beforeSemicolonShouldBeNoSpace(ushint& start);

    void correctIfWhileElse();
    void correctIf(ushint& indexLine);
    void correctWhile(ushint& indexLine);
    void correctElse(ushint& indexLine);

    void correctReturns();

    //for work whit braces
    //void updateBraces();						//Update in m_data
    //void updateBracesInAllData();
    void updateBracesText();	//In text

    void printBraces();
    void updateBracesAddNewLine(ushint indexDeleteLine);
    void updateBracesDeleteLine(ushint indexDeleteLine);
    shint returnFunctionStartIndex(ushint indexInFunctionBody);
    shint returnFunctionEndIndex(ushint indexInFunctionBody);
    //Work for line, update FileEditor functions
    //void addNewLineIndex(const unsigned short indexLine, const std::string& newLine);
    //void deleteLineIndex(const shint indexLine);

    //void addLineBetween(const shint indexLine, const shint indexSymbol, const std::string& newData);

    //void deleteInLineWithIndexLeft(const shint indexLine, const shint indexSymbol);
    //void deleteInLineWithIndexRight(const shint indexLine, const shint indexSymbol);

    //For initilization member data
    void initVaribleKeyWords();
    void addNewVaribleKeyWords(std::string keyWord);
    //void deleteVaribleKeyWords(std::string keyWord);

    void correctInitialization();
    void correctInitializationInFunction(int indexStartFunction, int indexEndFunction);

    bool searchInitializationInLine(ushint indexLine);




    void correctTabulations();
};


