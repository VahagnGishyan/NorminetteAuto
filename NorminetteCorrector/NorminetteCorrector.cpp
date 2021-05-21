#include "NorminetteCorrector.h"

//for work
int  NorminetteCorrector::searchSymbolsInLine(const std::string& line, const std::string& symbols)
{
    //function return negative, if symbol is not faund

    const std::string& reservData = line;
    for (ushint start = 0; start < reservData.size(); ++start)
    {
        for (ushint index = 0; index < symbols.size(); ++index)
        {
            if (reservData[start] == symbols[index])
                return start;
        }
    }
    return -1;
}
int  NorminetteCorrector::searchSymbolsInLine(int argIndex, const std::string& symbols)
{
    //function return negative, if symbol is not faund

    std::string reservData = FileEditor::getLine(argIndex);
    for (ushint start = 0; start < reservData.size(); ++start)
    {
        for (ushint index = 0; index < symbols.size(); ++index)
        {
            if (reservData[start] == symbols[index])
                return start;
        }
    }
    return -1;
}
bool NorminetteCorrector::searchInWords(const std::vector<std::string>& words, const std::string& keyWord)    //return true if found
{
    for (ushint start = 0; start < words.size(); ++start)
    {
        if (words[start] == keyWord)
        {
            return true;
        }
    }
    return false;
}
void NorminetteCorrector::divideLineIntoThreeNewLines(int indexLine, int indexLeft, int indexRight)
{
    std::string line = FileEditor::getLine(indexLine);

    //std::string leftData = "";
    std::string middleData = "";
    std::string rightData = "";

    for (ushint index = indexLeft; index <= indexRight; ++index)
    {
        middleData += line[index];
    }

    for (ushint index = indexRight + 1; index < line.size(); ++index)
    {
        rightData += line[index];
    }

    //targmanel angleren
    //left Data-yi hamar imast chuni nor togh steghcel
    //arden toghy ka, parzapes toghy poxum enq yst mer uzaci
    FileEditor::deleteInLine(indexLine, indexLeft, FileEditor::getLineSize(indexLine));
    FileEditor::addNewLine(indexLine + 1, middleData);
    FileEditor::addNewLine(indexLine + 2, rightData);
}

void                     NorminetteCorrector::addNewLine(int indexLine, const std::vector<std::string>& newLine)
{
    FileTextEditor::addNewLine(indexLine, newLine);
    NorminetteCorrector::updateBracesAddNewLine(indexLine);
}
void                     NorminetteCorrector::addNewLine(int indexLine, std::string& newLine)
{
    FileTextEditor::addNewLine(indexLine, newLine);
    NorminetteCorrector::updateBracesAddNewLine(indexLine);
}
void                     NorminetteCorrector::deleteLine(int indexLine)
{
    FileTextEditor::deleteLine(indexLine);
    NorminetteCorrector::updateBracesDeleteLine(FileTextEditor::size() - 2);
}

void                     NorminetteCorrector::addNewLineBack(const std::vector<std::string>& newLine)
{
    FileTextEditor::addNewLineBack(newLine);
    NorminetteCorrector::updateBracesAddNewLine(FileTextEditor::size() - 2);
}
void                     NorminetteCorrector::addNewLineBack(std::string& newLine)
{
    FileTextEditor::addNewLineBack(newLine);
    NorminetteCorrector::updateBracesAddNewLine(FileTextEditor::size() - 2);
}
void                     NorminetteCorrector::deleteLineBack()
{
    FileTextEditor::deleteLineBack();
    NorminetteCorrector::updateBracesDeleteLine(FileTextEditor::size());
}

//for work whit braces
void  NorminetteCorrector::updateBraces()
{
    if (FileTextEditor::empty())
    {
        std::cout << "Text is empty" << std::endl;
        return;
    }

    m_BracesIndex.clear();

    unsigned short countBracesStart = 0;
    unsigned short countBracesEnd = 0;
    unsigned short indexForBracesArr = -1;

    for (ushint start = 0; start < FileTextEditor::size(); ++start)
    {
        const std::string symbol = FileTextEditor::getLine(start)[0];
        ushint count = 0;

        if (symbol == "{")
        {
            if (countBracesStart == countBracesEnd)
            {
                ++indexForBracesArr;
                m_BracesIndex.resize(indexForBracesArr + 1);
            }
            m_BracesIndex[indexForBracesArr].push_back(start);
            ++countBracesStart;
        }
        if (symbol == "}")
        {
            m_BracesIndex[indexForBracesArr].push_back(-(start));
            ++countBracesEnd;
        }
    }
    m_BracesIndex.shrink_to_fit();
}
void  NorminetteCorrector::printBraces()
{
    if (m_BracesIndex.empty())
    {
        std::cout << "Braces is empty" << std::endl;
        return;
    }


    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        std::cout << "Function " << start << std::endl;

        for (ushint index = 0; index < m_BracesIndex[start].size(); ++index)
        {
            int indexLine = m_BracesIndex[start][index];

            if (indexLine > 0)
            {
                indexLine += m_startLine;
            }
            else
            {
                indexLine -= m_startLine;
            }
            std::cout << indexLine << ' ';
        }
        std::cout << std::endl;
    }
}
void  NorminetteCorrector::printBracesForText()
{
    if (m_BracesIndex.empty())
    {
        std::cout << "Braces is empty" << std::endl;
        return;
    }


    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        std::cout << "Function " << start << std::endl;

        for (ushint index = 0; index < m_BracesIndex[start].size(); ++index)
        {
            std::cout << m_BracesIndex[start][index] << ' ';
        }
        std::cout << std::endl;
    }
}
void  NorminetteCorrector::updateBracesAddNewLine(ushint indexDeleteLine)
{
    if (m_BracesIndex.empty())
        return;

    for (ushint start = 0; start < static_cast<ushint>(m_BracesIndex.size()); ++start)
    {
        if (indexDeleteLine > -m_BracesIndex[start].back())
            continue;
        for (ushint index = 0; index < static_cast<ushint>(m_BracesIndex[start].size()); ++index)
        {
            if (indexDeleteLine < getPositive(m_BracesIndex[start][index]))
            {
                if (m_BracesIndex[start][index] > 0)
                    ++m_BracesIndex[start][index];
                if (m_BracesIndex[start][index] < 0)
                    --m_BracesIndex[start][index];
            }
        }
    }
}
int   NorminetteCorrector::getPositive(int index)
{
    if (index >= 0)
        return index;
    else
        return -index;
}
void  NorminetteCorrector::updateBracesDeleteLine(ushint indexDeleteLine)
{
    if (m_BracesIndex.empty())
        return;

    for (ushint start = 0; start < static_cast<ushint>(m_BracesIndex.size()); ++start)
    {
        if (indexDeleteLine > -m_BracesIndex[start].back())
            continue;
        for (ushint index = 0; index < static_cast<ushint>(m_BracesIndex[start].size()); ++index)
        {
            if (indexDeleteLine < getPositive(m_BracesIndex[start][index]))
            {
                if (m_BracesIndex[start][index] > 0)
                    --m_BracesIndex[start][index];
                if (m_BracesIndex[start][index] < 0)
                    ++m_BracesIndex[start][index];
            }
        }
    }
}
shint NorminetteCorrector::getFunctionStart(ushint indexInFunctionBody)
{
    if (m_BracesIndex.empty())
        return -1;

    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        if (indexInFunctionBody > m_BracesIndex[start].front())
        {
            if (indexInFunctionBody < (-m_BracesIndex[start].back()))
            {
                return (m_BracesIndex[start].front() + 1);
            }
        }
    }
    return -1;
}
shint NorminetteCorrector::getFunctionEnd(ushint indexInFunctionBody)
{
    if (m_BracesIndex.empty())
        return -1;

    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        if (indexInFunctionBody > m_BracesIndex[start].front())
        {
            if (indexInFunctionBody < (-m_BracesIndex[start].back()))
            {
                return (-m_BracesIndex[start].back() - 1);
            }
        }
    }
    return -1;
}

//For corrector
void NorminetteCorrector::correctAll()
{
    if (!chackBasic())
    {
        std::cout << "Basic chack return false = error" << std::endl;
        return;
    }

    preliminaryCorrectingFileFormat();
    FileEditor::print();

    FileTextEditor::init(m_startLine, FileEditor::size());
    FileTextEditor::print();

    correctInsideLine();
    FileTextEditor::print();

    //correctForFinalize();

    //updata();
    //FileEditor::print();


}

//CodeBlock 1, basic check
bool NorminetteCorrector::chackBasic()
{
    if (preliminaryInspection())
    {
        std::cout << "ErrorCheckSpace::The file has few lines" << std::endl;
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
        FileEditor::addNewLine(heading42FormatLineSize, "");
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

//CodeBlock 2, Preliminary Correcting File Format
void NorminetteCorrector::preliminaryCorrectingFileFormat()
{
    bracesMustBeOnNewLine();
    afterSemicolonMustBeEmpty();
    unnecessarySpaces();
    deleteBlankLines();
}
void NorminetteCorrector::bracesMustBeOnNewLine()
{
    for (ushint start = m_startLine; start < FileEditor::size(); ++start)
    {
        int index = -1;
        std::string line = FileEditor::getLine(start);

        if (line == "{" || line == "}")
            continue;

        index = searchSymbolsInLine(line, "{}");
        if (index >= 0)
        {
            divideLineIntoThreeNewLines(start, index, index);
            ++start;
        }
    }
}
void NorminetteCorrector::afterSemicolonMustBeEmpty()
{
    for (ushint start = m_startLine; start < FileEditor::size(); ++start)
    {
        std::string line = FileEditor::getLine(start);
        int index = searchSymbolsInLine(line, ";");

        if (index < 0)
            continue;

        int indexEnd = FileEditor::getLineSize(start) - 1;
        if (index < indexEnd)
        {
            divideLineIntoThreeNewLines(start, index + 1, indexEnd);
        }
    }
}
void NorminetteCorrector::unnecessarySpaces()
{
    ushint endLine = size();

    for (ushint start = m_startLine; start < endLine; ++start)
    {
        std::vector<std::string> reservData;
        reservData = FileEditor::splitWordsBySpace(start);

        if (reservData.empty())
        {
            FileEditor::setLine(start, "");
            continue;
        }

        std::string newLine = reservData[0];
        for (ushint index = 1; index < reservData.size(); ++index)
        {
            newLine += " " + reservData[index];
        }
        FileEditor::setLine(start, newLine);
    }
}
void NorminetteCorrector::deleteBlankLines()
{
    for (ushint start = m_startLine; start < size(); ++start)
    {
        std::string line = FileEditor::getLine(start);

        if (line.empty())
        {
            FileEditor::deleteLine(start);
            --start;
        }
    }
}

//CodeBlock 3, correct Inside Line
void NorminetteCorrector::correctInsideLine()
{
    separateByKeySymbols();
    //correctSemicolon();
    //correctIfWhileElse();
    //correctReturns();
    //updateBracesText();
    //correctInitialization();
}

void NorminetteCorrector::separateByKeySymbols()
{
    for (ushint indexLine = 0; indexLine < FileTextEditor::size(); ++indexLine)
    {
        FileTextEditor::setLine(indexLine, separateLineByKeySymbols(indexLine));
    }
}
void NorminetteCorrector::addNewWords(std::vector<std::string>& words, const std::vector<std::string>& newWords)
{
    for (ushint start = 0; start < newWords.size(); ++start)
    {
        words.push_back(newWords[start]);
    }
}
std::vector<std::string> NorminetteCorrector::separateLineByKeySymbols(int indexLine)
{
    std::vector<std::string> words = FileTextEditor::getLine(indexLine);
    std::vector<std::string> newWords;
    ushint size = static_cast<ushint>(words.size());

    for (ushint start = 0; start < size; ++start)
    {
        addNewWords(newWords, separateWordByKeySymbols(words[start]));
    }
    return (newWords);
}
std::vector<std::string> NorminetteCorrector::separateWordByKeySymbols(const std::string& word)
{
    std::vector<std::string> newWords;

    std::string newWord = "";
    for (ushint index = 0; index < word.size(); ++index)
    {

        const char symbol = word[index];

        if (std::isalpha(symbol) || std::isdigit(symbol) || symbol == '_')
        {
            newWord += symbol;
            continue;
        }

        if (newWord.empty())
        {
            newWord += symbol;
            newWords.push_back(newWord);
            newWord = "";
            continue;
        }

        newWords.push_back(newWord);
        newWord = "";

        if (std::isspace(symbol))
        {
            continue;
        }

        newWord = symbol;
        newWords.push_back(newWord);
        newWord = "";
    }
    if (!newWord.empty())
    {
        newWords.push_back(newWord);
    }

    return (newWords);
}


//void NorminetteCorrector::correctSemicolon()
//{
//    if (m_text.empty())
//        return;
//    for (ushint indexLine = 0; indexLine < m_text.size(); ++indexLine)
//    {
//        if (m_text[indexLine].size() == 1 && m_text[indexLine][0] == ";")
//        {
//            aloneSemicolonRaiseUp(indexLine);
//        }
//        deleteUnnecessarySemicolon(indexLine);
//        //beforeSemicolonShouldBeNoSpace(indexLine, text);
//    }
//}
//void NorminetteCorrector::aloneSemicolonRaiseUp(ushint& indexLine)
//{
//    if (indexLine == 9)
//        std::cout;
//    m_text[indexLine - 1].back() = m_text[indexLine - 1].back() + ";";
//
//    for (ushint start = indexLine; start < m_text.size() - 1; ++start)
//    {
//        m_text[start] = m_text[start + 1];
//    }
//    m_text.pop_back();
//
//    --indexLine;
//}
//void NorminetteCorrector::deleteUnnecessarySemicolon(ushint& indexLine)
//{
//    std::string line = m_text[indexLine].back();
//
//    if (line.empty() || line.size() == 1 || line.back() != ';')
//        return;
//    for (shint index = static_cast<shint>(line.size()) - 2; index >= 0; --index)
//    {
//        if (line[index] == ';')
//            line.pop_back();
//    }
//
//    m_text[indexLine].back() = line;
//}
//void NorminetteCorrector::beforeSemicolonShouldBeNoSpace(ushint& indexLine)
//{
//    std::vector <std::string> line = m_text[indexLine];
//
//    int indexLineEnd = static_cast<int>(line.size()) - 1;
//
//    if (indexLineEnd == 0 || line[indexLineEnd] != ";")
//        return;
//
//    line[indexLineEnd - 1] += line[indexLineEnd];
//    line.pop_back();
//    m_text[indexLine] = line;
//
//}
//
//void NorminetteCorrector::correctIfWhileElse()
//{
//    for (ushint indexLine = 0; indexLine < m_text.size(); ++indexLine)
//    {
//        correctIf(indexLine);
//        correctWhile(indexLine);
//        correctElse(indexLine);
//    }
//}
//void NorminetteCorrector::correctIf(ushint& indexLine)
//{
//    //after if should be no space
//
//    std::vector<std::string>& line = m_text[indexLine];
//    const std::string keyWord = "if";
//
//    if (!searchInWords(line, keyWord))
//    {
//        return;
//    }
//
//    ushint start = 0;
//    while (line[start] != keyWord && start < line.size())
//        ++start;
//    ++start;
//
//    shint count = 0;
//
//    for (; start < line.size(); ++start)
//    {
//        if (line[start] == "(")
//            ++count;
//        else if (line[start] == ")")
//            --count;
//        if (count == 0)
//            break;
//    }
//
//    if (start == line.size() - 1)
//        return;
//
//    std::vector<std::string> newData;
//
//    for (ushint index = start + 1; index < line.size(); ++index)
//    {
//        newData.push_back(line[index]);
//    }
//
//    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start; --index)
//    {
//        line.pop_back();
//    }
//
//    addNewLineInTextIndex(indexLine + 1, newData);
//
//    //std::vector<std::string> forNotError;
//    //forNotError[0] = "{";
//    ////addNewLineInTextIndex(indexLine + 1, text, "{");
//    //addNewLineInTextIndex(indexLine + 1, text, forNotError);
//    //addNewLineInTextIndex(indexLine + 2, text, newData);
//    ////addNewLineInTextIndex(indexLine + 3, text, "}");
//    //forNotError[0] = "}";
//    //addNewLineInTextIndex(indexLine + 3, text, forNotError);
//}
//void NorminetteCorrector::correctWhile(ushint& indexLine)
//{
//    //after while should be no space
//
//    std::vector<std::string>& line = m_text[indexLine];
//    const std::string keyWord = "while";
//
//    if (!searchInWords(line, keyWord))
//    {
//        return;
//    }
//
//    ushint start = 0;
//    while (line[start] != keyWord && start < line.size())
//        ++start;
//    ++start;
//
//    shint count = 0;
//
//    for (; start < line.size(); ++start)
//    {
//        if (line[start] == "(")
//            ++count;
//        else if (line[start] == ")")
//            --count;
//        if (count == 0)
//            break;
//    }
//
//    if (start == line.size() - 1)
//        return;
//
//    std::vector<std::string> newData;
//
//    for (ushint index = start + 1; index < line.size(); ++index)
//    {
//        newData.push_back(line[index]);
//    }
//
//    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start; --index)
//    {
//        line.pop_back();
//    }
//
//    addNewLineInTextIndex(indexLine + 1, newData);
//}
//void NorminetteCorrector::correctElse(ushint& indexLine)
//{
//    //after else should be no space
//
//    std::vector<std::string>& line = m_text[indexLine];
//    const std::string keyWord = "else";
//
//    if (!searchInWords(line, keyWord))
//    {
//        return;
//    }
//
//    if (line.size() < 2)
//        return;
//
//    ushint start = 0;
//    while (line[start] != keyWord && start < line.size())
//        ++start;
//    ++start;
//
//    if (start == line.size() - 1)
//        return;
//
//    if (line[start] == "if")
//        return;
//
//    std::vector<std::string> newData;
//
//    for (ushint index = start; index < line.size(); ++index)
//    {
//        newData.push_back(line[index]);
//    }
//
//    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start - 1; --index)
//    {
//        line.pop_back();
//    }
//
//    addNewLineInTextIndex(indexLine + 1, newData);
//}
//
//void NorminetteCorrector::correctReturns()
//{
//    for (ushint indexLine = 0; indexLine < m_text.size(); ++indexLine)
//    {
//        std::vector<std::string>& line = m_text[indexLine];
//
//        const std::string keyWord = "return";
//
//        if (line.size() < 3 || !searchInWords(line, keyWord))
//            continue;
//
//        //for testing, not for relise
//        assert(line.front() == keyWord && "Whil be a return");
//
//        if (line[1] == "(")
//            continue;
//
//        std::vector<std::string> data;
//
//        data.push_back(line.front());
//        data.push_back("(");
//
//        for (ushint index = 1; index < line.size() - 1; ++index)
//        {
//            data.push_back(line[index]);
//        }
//
//        data.push_back(")");
//        data.push_back(line.back());
//
//        line = data;
//    }
//
//}
//

//
////For initilization member data
//void NorminetteCorrector::initVaribleKeyWords()
//{
//    if (!m_varibleKeyWords.empty())
//    {
//        m_varibleKeyWords.clear();
//    }
//
//
//    m_varibleKeyWords.reserve(9);
//
//    m_varibleKeyWords.push_back("short");
//    m_varibleKeyWords.push_back("ushort");
//    m_varibleKeyWords.push_back("ushint");
//    m_varibleKeyWords.push_back("int");
//    m_varibleKeyWords.push_back("uint");
//    m_varibleKeyWords.push_back("long");
//    m_varibleKeyWords.push_back("ulong");
//    m_varibleKeyWords.push_back("float");
//    m_varibleKeyWords.push_back("double");
//
//    assert(m_varibleKeyWords.size() == 9 && "size whil be 9");
//}
//void NorminetteCorrector::addNewVaribleKeyWords(std::string keyWord)
//{
//    m_varibleKeyWords.push_back(keyWord);
//}
////void NorminetteCorrector::deleteVaribleKeyWords(std::string keyWord)
////{
////    for()
////    m_varibleKeyWords.push_back(keyWord);
////}
//
//void NorminetteCorrector::correctInitialization()
//{
//    if (m_BracesIndex.empty())
//        updateBracesText();
//
//    if (m_BracesIndex.empty())
//        return;
//
//    if (m_varibleKeyWords.empty())
//        initVaribleKeyWords();
//
//    printText();
//    printBracesForText();
//
//    //for test
//    ushint size = static_cast<ushint>(m_BracesIndex.size());
//
//    for (ushint start = 0; start < size; ++start)
//    {
//        if (start == 4)
//        {
//            printText();
//            printBracesForText();
//        }
//        correctInitializationInFunction(m_BracesIndex[start].front() + 1, -m_BracesIndex[start].back() - 1);
//    }
//
//    m_varibleKeyWords.clear();
//}
//void NorminetteCorrector::correctInitializationInFunction(int indexStartFunction, int indexEndFunction)
//{
//    if (indexStartFunction < 0 || indexEndFunction < 0)
//    {
//        std::cerr << "arguments is negative" << std::endl;
//        std::cout << "indexStartFunction = " << indexStartFunction << std::endl;
//        std::cout << "indexEndFunction = " << indexEndFunction << std::endl;
//        return;
//    }
//
//    ushint startDeclaration = searchDeclarationStartInFunctionIndex(indexStartFunction, indexEndFunction);
//
//    //for test
//    std::cout << "Function start = " << indexStartFunction << "  " << "Function End = " << indexEndFunction << std::endl;
//    std::cout << startDeclaration << std::endl;
//
//
//    for (ushint start = startDeclaration; start <= NorminetteCorrector::getFunctionEndIndex(start); ++start)
//    {
//        if (!isThereDeclarationInTextLine(start))
//        {
//            continue;
//        }
//        if (isThereAssignmentInTextLine(start))
//        {
//            separateDeclarationFromAssignment(startDeclaration, start);
//        }
//        else
//        {
//            raiseDeclarationUp(startDeclaration, start);
//        }
//        std::cout << "Init line index :: " << start << std::endl;
//    }
//}
//ushint NorminetteCorrector::searchDeclarationStartInFunctionIndex(int indexStartFunction, int indexEndFunction)
//{
//    if (m_text.size() == 1 && m_text[indexStartFunction].front() == "{")
//    {
//        ++indexStartFunction;
//    }
//    if (m_text.size() == 1 && m_text[indexStartFunction].front() == "}")
//    {
//        --indexEndFunction;
//    }
//
//    if (indexStartFunction < 0 || indexEndFunction < 0)
//    {
//        std::cerr << "arguments is negative" << std::endl;
//        std::cout << "indexStartFunction = " << indexStartFunction << std::endl;
//        std::cout << "indexEndFunction = " << indexEndFunction << std::endl;
//        return (0);
//    }
//
//    for (ushint indexLine = indexStartFunction; indexLine < getFunctionEndIndex(indexLine); ++indexLine)
//    {
//        if (!isThereDeclarationInTextLine(indexLine))
//        {
//            return (indexLine);
//        }
//        else
//        {
//            if (isThereAssignmentInTextLine(indexLine))
//            {
//                return (indexLine);
//            }
//        }
//    }
//
//    return (indexStartFunction + 1);
//}
//bool NorminetteCorrector::isThereDeclarationInTextLine(ushint indexLine)
//{
//    std::vector<std::string> line = m_text[indexLine];
//
//    if (m_varibleKeyWords.empty())
//    {
//        NorminetteCorrector::initVaribleKeyWords();
//    }
//
//    for (ushint start = 0; start < line.size(); ++start)
//    {
//        for (ushint index = 0; index < m_varibleKeyWords.size(); ++index)
//        {
//            if (searchInWords(line, m_varibleKeyWords[index]))
//            {
//                return true;
//            }
//        }
//    }
//    return false;
//}
//bool NorminetteCorrector::isThereAssignmentInTextLine(ushint indexLine)
//{
//    std::vector<std::string> line = m_text[indexLine];
//
//    for (shint start = static_cast<shint>(line.size() - 1); start >= 0; --start)
//    {
//        if (line[start] == "=")
//        {
//            return true;
//        }
//    }
//    return false;
//}
//void NorminetteCorrector::separateDeclarationFromAssignment(ushint& startDeclaration, ushint indexLine)
//{
//    std::vector<std::string> line = m_text[indexLine];
//
//    std::vector<std::string> newLine;
//
//    ushint start = 0;
//    for (; start < line.size(); ++start)
//    {
//        if (line[start] == "=")
//        {
//            break;
//        }
//        newLine.push_back(line[start]);
//    }
//    newLine.push_back(";");
//    NorminetteCorrector::addNewLineInTextIndex(startDeclaration, newLine);
//    ++startDeclaration;
//
//    newLine.clear();
//
//    newLine.push_back(line[start - 1]);
//
//    for (; start < line.size(); ++start)
//    {
//        newLine.push_back(line[start]);
//    }
//
//    m_text[indexLine + 1] = newLine;
//}
//void NorminetteCorrector::raiseDeclarationUp(ushint& startDeclaration, ushint& indexLine)
//{
//    std::vector<std::string> line = m_text[indexLine];
//
//    NorminetteCorrector::deleteLineInTextIndex(indexLine);
//
//    NorminetteCorrector::addNewLineInTextIndex(startDeclaration, line);
//    ++startDeclaration;
//    --indexLine;
//}
//bool NorminetteCorrector::isThereInitializationInTextLine(ushint indexLine)
//{
//
//}