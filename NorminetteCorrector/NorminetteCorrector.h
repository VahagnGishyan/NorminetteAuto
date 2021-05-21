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
    int  getPositive(int index);
    int searchSymbolsInLine(const std::string& line, const std::string& symbols);
    int searchSymbolsInLine(int index, const std::string& symbols);
    void divideLineIntoThreeNewLines(int indexLine, int indexLeft, int indexRight);

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



};

