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
    //ushint				    m_startLine;
    //std::vector<unsigned short>	    m_PreprocessorIndex;
    std::vector<std::vector<short>>	    m_BracesIndex;
    //std::vector<bool>			    m_ErrorStatusRegister;
    //std::vector<std::string>		    m_varibleKeyWords;

public:
    NorminetteCorrector() : FileTextEditor()
    {

    }
    NorminetteCorrector(std::string filename) : FileTextEditor()
    {
	
    }

    //Work with member braces index
    int  getPositive(int index);

    //For corrector
    void correctAll();

    //CodeBlock 1, correct header
    void chackHeader();

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



};

