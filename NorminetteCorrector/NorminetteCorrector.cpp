#include "NorminetteCorrector.h"

//for work
//int NorminetteCorrector::searchSymbolsInLine(const std::string& line, const std::string& symbols)
//{
//    //function return negative, if symbol is not faund
//
//    //const std::string& reservData = line;
//    //for (ushint start = 0; start < reservData.size(); ++start)
//    //{
//    //    for (ushint index = 0; index < symbols.size(); ++index)
//    //    {
//    //        if (reservData[start] == symbols[index])
//    //            return start;
//    //    }
//    //}
//    //return -1;
//}
//int NorminetteCorrector::searchSymbolsInLine(int argIndex, const std::string& symbols)
//{
//    //function return negative, if symbol is not faund
//
//    //std::string reservData = FileEditor::getLineIndex(argIndex);
//    //for (ushint start = 0; start < reservData.size(); ++start)
//    //{
//    //    for (ushint index = 0; index < symbols.size(); ++index)
//    //    {
//    //        if (reservData[start] == symbols[index])
//    //            return start;
//    //    }
//    //}
//    //return -1;
//}
//void NorminetteCorrector::divideLineIntoThreeNewLines(int indexLine, int indexLeft, int indexRight)
//{
//    //std::string line = FileEditor::getLineIndex(indexLine);
//
//    ////std::string leftData = "";
//    //std::string middleData = "";
//    //std::string rightData = "";
//
//    //for (ushint index = indexLeft; index <= indexRight; ++index)
//    //{
//    //    middleData += line[index];
//    //}
//
//    //for (ushint index = indexRight + 1; index < line.size(); ++index)
//    //{
//    //    rightData += line[index];
//    //}
//
//    ////targmanel angleren
//    ////left Data-yi hamar imast chuni nor togh steghcel
//    ////arden toghy ka, parzapes toghy poxum enq yst mer uzaci
//    //FileEditor::deleteInLineWithIndexRight(indexLine, indexLeft - 1);
//    //FileEditor::addNewLineIndex(indexLine + 1, middleData);
//    //FileEditor::addNewLineIndex(indexLine + 2, rightData);
//}

//For corrector
void NorminetteCorrector::correctAll()
{
    FileEditor::print();

    if (!chackBasic())
    {
        return;
    }

    FileTextEditor::print();

    //preliminaryCorrectingFileFormat();
    //FileEditor::print();

    ////correctInsideLine();

    ////correctForFinalize();

    //updata();
    //FileEditor::print();


}

//CodeBlock old
bool NorminetteCorrector::chackBasic()
{
    if (preliminaryInspection())
    {
        std::cout << "ErrorCheckSpace::�he file has few lines" << std::endl;
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

    initText(m_startLine);
    return true;
}
bool NorminetteCorrector::preliminaryInspection()
{
    unsigned short lineSize = FileEditor::size();
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
        if (FileEditor::getLine(start)[0] != '/')
            return true;
        if (FileEditor::getLine(start).size() != 80)
            return true;
    }
    if (FileEditor::getLine(heading42FormatLineSize).size() != 0)
    {
        FileEditor::addNewLine(heading42FormatLineSize, "");
    }
    m_startLine = heading42FormatLineSize + 1;

    return false;
}
bool NorminetteCorrector::checkPreprocessor()
{
    unsigned short dataLineCount = FileEditor::size();
    unsigned short start = m_startLine;
    for (; start < dataLineCount; ++start)
    {
        if (FileEditor::getLine(start)[0] != '#')
        {
            break;
        }
    }
    if (FileEditor::getLine(start).size() != 0)
        FileEditor::addNewLine(start, "");
    m_startLine = start + 1;
    return false;
}
void NorminetteCorrector::initText(int startLine)
{
    //Jamanakavor tarberak
    FileTextEditor::init(startLine, FileEditor::size());
}

//Block 1, basic check
//bool NorminetteCorrector::chackFile()
//{
//    if (preliminaryInspectionNEW())
//    {
//        std::cout << "Error in preliminary inspection" << std::endl;
//        std::cout << "Enter 0 for break or 1 for continue" << std::endl;
//
//        bool result;
//        std::cin >> result;
//        if (!result)
//        {
//            return (true);
//        }
//    }
//    if (checkFormatHeading42NEW())
//    {
//        std::cout << "Error in check format heading 42" << std::endl;
//        std::cout << "Enter 0 for break or 1 for correct" << std::endl;
//
//        bool result;
//        std::cin >> result;
//        if (result)
//        {
//            correctFormatHeading42NEW();
//        }
//        else
//        {
//            return (true);
//        }
//    }
//    if (checkPreprocessorNEW())
//    {
//        std::cout << "Error in check preprocessor" << std::endl;
//        std::cout << "Enter 0 for break or 1 for correct" << std::endl;
//        
//        bool result;
//        std::cin >> result;
//        if (result)
//        {
//            correctPreprocessorNEW();
//        }
//        else
//        {
//            return (true);
//        }
//    }
//    return (false);
//}
//
//bool NorminetteCorrector::preliminaryInspectionNEW()
//{
//    unsigned short lineSize = FileTextEditor::size();
//    unsigned short lineSizeMin = 13;                    //10 header + 3 function line count
//    if (lineSize < lineSizeMin)
//    {
//        return true;
//    }
//    return false;
//}
//bool NorminetteCorrector::checkFormatHeading42NEW()
//{
//    unsigned short heading42FormatLineSize = 11;
//    unsigned short start = 0;
//
//    for (; start < heading42FormatLineSize; ++start)
//    {
//        if (FileTextEditor::getLine(start).front() != "/*" &&
//            FileTextEditor::getLine(start).back()  != "*/")
//        {
//            return true;
//        }
//    }
//    if (FileEditor::getLine(heading42FormatLineSize).size() != 0)
//        FileEditor::addNewLine(heading42FormatLineSize, "");
//    return false;
//}
//void NorminetteCorrector::correctFormatHeading42NEW()
//{
//
//}
//bool NorminetteCorrector::checkPreprocessorNEW()
//{
//    //unsigned short dataLineCount = size();
//    //unsigned short start = m_startLine;
//    //for (; start < dataLineCount; ++start)
//    //{
//    //    if (FileEditor::getLine(start)[0] != '#')
//    //    {
//    //        break;
//    //    }
//    //}
//    //if (FileEditor::getLine(start).size() != 0)
//    //    FileEditor::addNewLine(start, "");
//    //m_startLine = start + 1;
//    return false;
//}
//void NorminetteCorrector::correctPreprocessorNEW()
//{
//
//}

////Block 2, Preliminary Correcting File Format
//void NorminetteCorrector::preliminaryCorrectingFileFormat()
//{
//    bracesMustBeOnNewLine();
//    afterSemicolonMustBeEmpty();
//    unnecessarySpaces();
//    deleteBlankLines();
//}
//void NorminetteCorrector::bracesMustBeOnNewLine()
//{
//    for (ushint start = m_startLine; start < size(); ++start)
//    {
//        int index = -1;
//        std::string line = FileEditor::getLine(start);
//
//        if (line == "{" || line == "}")
//            continue;
//
//        index = searchSymbolsInLine(line, "{}");
//        if (index >= 0)
//        {
//            divideLineIntoThreeNewLines(start, index, index);
//            ++start;
//        }
//    }
//}
//void NorminetteCorrector::afterSemicolonMustBeEmpty()
//{
//    for (ushint start = m_startLine; start < size(); ++start)
//    {
//        std::string line = FileEditor::getLine(start);
//        int index = searchSymbolsInLine(line, ";");
//
//        if (index < 0)
//            continue;
//
//        int indexEnd = FileEditor::getIndexLineEnd(start) - 1;
//        if (index < indexEnd)
//        {
//            divideLineIntoThreeNewLines(start, index + 1, indexEnd);
//        }
//    }
//}
//void NorminetteCorrector::unnecessarySpaces()
//{
//    ushint endLine = size();
//
//    for (ushint start = m_startLine; start < endLine; ++start)
//    {
//        std::vector<std::string> reservData;
//        reservData = FileEditor::separateBySpaces(start);
//
//        if (reservData.empty())
//        {
//            FileEditor::setLine(start, "");
//            continue;
//        }
//
//        std::string newLine = reservData[0];
//        for (ushint index = 1; index < reservData.size(); ++index)
//        {
//            newLine += " " + reservData[index];
//        }
//        FileEditor::setLine(start, newLine);
//    }
//}
//void NorminetteCorrector::deleteBlankLines()
//{
//    for (ushint start = m_startLine; start < size(); ++start)
//    {
//        std::string line = FileEditor::getLine(start);
//
//        if (line.empty())
//        {
//            FileEditor::deleteLine(start);
//            --start;
//        }
//    }
//}
////void NorminetteCorrector::correctTabulations()
////{
////    //correctBrackets
////}
////void NorminetteCorrector::correctBrackets()
////{
////
////}