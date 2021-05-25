#pragma once
#include "..\Header.h"
#include "..\FileTextEditor\FileTextEditor.h"

//CodeBlock 0       : FileEditor, FileTextEditor
//CodeBlock 1,2,3,4 : NorminetteCorrector
//CodeBlock 5       : NorminetteAuto

class NorminetteCorrector : public FileTextEditor
{
private:
    //Variables
    ushint				    m_startLine;
    //std::vector<unsigned short>	    m_PreprocessorIndex;
    std::vector<std::vector<short>>	    m_BracesIndex;
    //std::vector<bool>			    m_ErrorStatusRegister;
    //std::vector<std::string>		    m_varibleKeyWords;

public:
    NorminetteCorrector() : FileTextEditor(), m_startLine(0)
    {

    }
    NorminetteCorrector(std::string filename) : FileTextEditor(), m_startLine(0)
    {
	FileEditor::openFile(filename);
    }

    // heto dardznel mi masy private
public:

    //for work
    int  getPositive(int index) const;
    int  searchSymbolsInLine(const std::string& line, const std::string& symbols);
    int  searchSymbolsInLine(int index, const std::string& symbols);
    bool searchInWords(const std::vector<std::string>& words, const std::string& keyWord);    //return true if found
    void divideLineIntoThreeNewLines(int indexLine, int indexLeft, int indexRight);
    //void                     combineWords(ushint indexLine, ushint& indexLeftWord, ushint indexRightWord);
    bool isdigit(const std::string& word) const;

    void                     addNewLine(int indexLine, const std::vector<std::string>& newLine);
    void                     addNewLine(int indexLine, const std::string& newLine);
    void                     deleteLine(int indexLine);

    void                     addNewLineBack(const std::vector<std::string>& newLine);
    void                     addNewLineBack(std::string& newLine);
    void                     deleteLineBack();

    void updata();
    bool isTabulation(const std::string& word);

    //For corrector
    void correctAll();

    //CodeBlock 1, basic check
    bool chackBasic();
    bool preliminaryInspection();
    bool checkFormatHeading42();
    bool checkPreprocessor();

    //CodeBlock 2, Preliminary Correcting File Format
    void preliminaryCorrectingFileFormat();
    void bracesMustBeOnNewLine();
    //void correctSemicolon();
    void afterSemicolonMustBeEmpty();
    void unnecessarySpaces();
    void deleteBlankLines();

    //CodeBlock 3, correct Inside Line
    void correctInsideLine();

    void separateByKeySymbols();     //key symbols, " ", (), [], =, +, ...
    std::vector<std::string> separateLineByKeySymbols(int indexLine);
    void addNewWords(std::vector<std::string>& words, const std::vector<std::string>& newWords);
    std::vector<std::string> separateWordByKeySymbols(const std::string& Words);
    void separateStringInLine(const std::string& line, std::vector<std::string>& words, ushint& index);

    void correctSemicolon();
    void aloneSemicolonRaiseUp(ushint& start);
    void deleteUnnecessarySemicolon(ushint& indexLine);


    void correctIfWhileElse();
    void correctIf(ushint& indexLine);
    void correctWhile(ushint& indexLine);
    void correctElse(ushint& indexLine);

    void correctReturns();

    //for work whit braces
    void  updateBraces();
    void  printBraces();
    void  printBracesWhithHeader();
    void  printBracesForText();
    void  updateBracesAddNewLine(ushint indexDeleteLine);
    void  updateBracesDeleteLine(ushint indexDeleteLine);
    shint getFunctionStart(ushint indexInFunctionBody);
    shint getFunctionEnd(ushint indexInFunctionBody);

    //For initilization member data
    void initVaribleKeyWords(std::vector<std::string>& varibleKeyWords);
    void addNewVaribleKeyWords(std::vector<std::string>& varibleKeyWords, std::string keyWord);

    void correctInitialization();
    void correctInitializationInFunction(std::vector<std::string> varibleKeyWords, int indexStartFunction, int indexEndFunction);
    ushint searchDeclarationStartInFunction(std::vector<std::string> varibleKeyWords, int indexStartFunction, int indexEndFunction);
    bool isThereDeclarationInLine(std::vector<std::string>& varibleKeyWords, ushint indexLine);
    bool isThereAssignmentInLine(ushint indexLine);
    void separateDeclarationFromAssignment(ushint& startDeclaration, ushint indexLine);
    void raiseDeclarationUp(ushint& startDeclaration, ushint& indexLine);
    bool isWordDeclarationKeyWord(const std::vector<std::string>& varibleKeyWords, const std::string& word) const;

    //CodeBlock 4, final corrections
    void correctForFinalize();

    void correctMathOperators();
    void correctMathOperatorsInFunction(ushint startFunction, ushint endFunction);
    void searchMathOperatorsInLine(ushint indexLine);
    void correctMathOperatorsInLine(ushint indexLine, ushint& indexWord);
    void searchUnaryMathOperatorInLine(ushint indexLine, std::vector<std::string>& line);
    void searchBinaryMathOperatorInLine(ushint indexLine, std::vector<std::string>& line);

    bool isFirstWordUnaryMathOperator(std::vector<std::string>& line);
    bool isUnaryMathOperator(ushint indexLine, std::vector<std::string>& line, ushint& indexWord);
    bool isWordUnaryMathOperator(const std::string& word);

    bool isMathOperator(const std::string& symbol) const;
    bool isPointerOrReferenceMathOperator(const std::string& word) const;
    bool isPointerMathOperator(const std::string& word) const;
    bool isReferenceMathOperator(const std::string& word) const;
    bool isPointerMathOperator(const char symbol) const;
    bool isReferenceMathOperator(const char symbol) const;
    bool isIncrementOrDecrement(const std::string& word) const;

    void correctIncrementOrDecrement(ushint indexLine, ushint indexWord);
    //void correctPointerOrReferenceMathOperator(ushint indexLine, ushint indexWord);
    int  latestMathOperatorIndex(ushint indexLine, ushint indexWord);
    int  latestMathOperatorIndex(std::vector<std::string>& line, ushint indexWord);
    //void deleteSpacesBetweenMathOperators();

    void correctBrackets();
    void correctRoundBrackets();
    void searchBracketsInLine(int indexLine);
    void correctOpenRoundBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord);
    void correctCloseRoundBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord);
    void correctOpenSquareBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord);
    void correctCloseSquareBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord);

    void beforeSemicolonShouldBeNoSpace();
    void correctComma();
    void correctCommaInLine(ushint indexLine);

    void   correctTabulation();
    void   correctTabulationInFunction(ushint indexStart, ushint indexEnd);
    void   correctTabulationInLine(ushint indexLine);
    ushint getTabulationCount(ushint indexLine);
    ushint getTabulationCountInFunction(ushint indexFunction, ushint indexLine);
    bool   isBracesIndex(const ushint indexLine) const;

    void   correctTabulationBeforeVariableNames();
    void   searchFunctionNames(std::vector<ushint>& indexDeclarationLine);
    void   searchDeclarationVaribaleNames(std::vector<ushint>& indexDeclarationLine, std::vector<std::string>& varibleKeyWords);
    void   searchDeclarationVaribaleNamesInFuntion(std::vector<ushint>& indexDeclarationLine, ushint indexFunction, std::vector<std::string>& varibleKeyWords);
    std::vector<ushint> getIndexKeyWordsOfTabulationForVaribaleAndFunctionNames(const std::vector<ushint>& indexDeclarationLine, std::vector<std::string>& varibleKeyWords);
    std::vector<ushint> getSizeKeyWordsOfTabulationForVaribaleAndFunctionNames(const std::vector<ushint>& indexDeclarationLine, const std::vector<ushint>&);
    shint getDeclarationSizeInFunction(ushint indexDeclaration, const std::vector<std::string>& varibleKeyWords);
    shint getDeclarationKeyWordIndexInLine(const std::vector<std::string>& line, const std::vector<std::string>& varibleKeyWords);
    shint getDeclarationSizeInLine(const std::vector<std::string>& line, ushint indexWord);
    void  correctTabulationForVaribaleAndFunctionNames(const std::vector<ushint>& indexDeclarationLine, const std::vector<ushint>& indexKeyWord, std::vector<ushint> sizeKeyWord);
    shint getMaxDeclarationSize(const std::vector<ushint>& indexDeclarationLine);
    std::string initTabCountWord(int count);
    bool isDeclarationLineFunctionName(ushint indexLine);

    void addFewerLines();
    void addFewerLinesAToFunctions();
    void addFewerLinesAToDeclaration();

};

