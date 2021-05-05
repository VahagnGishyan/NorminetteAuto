#include "NorminetteCorrector.h"

//initialization 
NorminetteCorrector::NorminetteCorrector() : FileEditor()
{

}
NorminetteCorrector::NorminetteCorrector(std::string filename) : FileEditor(filename)
{

}

//For corrector
void NorminetteCorrector::correctAll()
{
    if (!chackBasic())
    {
        std::cout << "Basic chack return false = error" << std::endl;
        return;
    }


}

//Block 1, basic check
bool NorminetteCorrector::chackBasic()
{
    if (preliminaryInspection())
    {
        std::cout << "ErrorCheckSpace::Òhe file has few lines" << std::endl;
        return false;
    }

    if (checkFormatHeading42())
    {
        std::cout << "ErrorStatusName::header42" << std::endl;
        //doSomething
        return false;
    }

    if (checkPreprocessor())
    {
        std::cout << "ErrorStatusName::preprocessor" << std::endl;
        //doSomething
        return false;
    }

    return true;
}
bool NorminetteCorrector::preliminaryInspection()
{
    unsigned short lineSize = size();
    unsigned short lineSizeMin = 13;                    //10 header + 3 function line count
    if (lineSize < lineSizeMin)
    {
        return true;
    }
    return false;
}
bool NorminetteCorrector::checkFormatHeading42()
{
    unsigned short heading42FormatLineSize = 11;
    unsigned short start = 0;

    for (; start < heading42FormatLineSize; ++start)
    {
        if (FileEditor::at(start)[0] != '/')
            return true;
        if(FileEditor::at(start).size() != 80)
            return true;
    }
    if (at(heading42FormatLineSize).size() != 0)
       addNewLineIndex(heading42FormatLineSize, "");
    m_startLine = heading42FormatLineSize + 1;
    return false;
}
bool NorminetteCorrector::checkPreprocessor()
{
    unsigned short dataLineCount = size();
    unsigned short start = m_startLine;
    for (; start < dataLineCount; ++start)
    {
        if (at(start)[0] != '#')
        {
            break;
        }
    }
    if (at(start).size() != 0)
        addNewLineIndex(start, "");
    m_startLine = start + 1;
    return false;
}

//Block 1, basic check
void NorminetteCorrector::preliminaryCorrectingFileFormat()
{

}
