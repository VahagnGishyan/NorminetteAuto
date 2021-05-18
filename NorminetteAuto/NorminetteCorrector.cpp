#include "NorminetteCorrector.h"

//for work
void NorminetteCorrector::printText()
{
    std::cout << "\n\n\n";
    std::cout << "Start print text" << std::endl;

    for (ushint indexLine = 0; indexLine < m_text.size(); ++indexLine)
    {
        std::cout << indexLine << "\t";
        for (ushint index = 0; index < m_text[indexLine].size(); ++index)
        {
            std::cout << m_text[indexLine][index] << " ";
        }
        std::cout << std::endl;
    }
}
int NorminetteCorrector::searchSymbolsInLine(const std::string& line, const std::string& symbols)
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
int NorminetteCorrector::searchSymbolsInLineIndex(int argIndex, const std::string& symbols)
{
    //function return negative, if symbol is not faund

    std::string reservData = FileEditor::getLineIndex(argIndex);
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
void NorminetteCorrector::divideLineIntoThreeNewLines(int indexLine, int indexLeft, int indexRight)
{
    std::string line = FileEditor::getLineIndex(indexLine);
    
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
    FileEditor::deleteInLineWithIndexRight(indexLine, indexLeft - 1);
    FileEditor::addNewLineIndex(indexLine + 1, middleData);
    FileEditor::addNewLineIndex(indexLine + 2, rightData);
}

//For corrector
void NorminetteCorrector::correctAll()
{
    if (!chackBasic())
    {
        std::cout << "Basic chack return false = error" << std::endl;
        return;
    }

    FileEditor::print();
    
    preliminaryCorrectingFileFormat();
    FileEditor::print();

    correctInsideLine();

    correctForFinalize();

    updata();
    FileEditor::print();


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
        if (FileEditor::getLineIndex(start)[0] != '/')
            return true;
        if(FileEditor::getLineIndex(start).size() != 80)
            return true;
    }
    if (FileEditor::getLineIndex(heading42FormatLineSize).size() != 0)
        FileEditor::addNewLineIndex(heading42FormatLineSize, "");
    m_startLine = heading42FormatLineSize + 1;
    return false;
}
bool NorminetteCorrector::checkPreprocessor()
{
    unsigned short dataLineCount = size();
    unsigned short start = m_startLine;
    for (; start < dataLineCount; ++start)
    {
        if (FileEditor::getLineIndex(start)[0] != '#')
        {
            break;
        }
    }
    if (FileEditor::getLineIndex(start).size() != 0)
        FileEditor::addNewLineIndex(start, "");
    m_startLine = start + 1;
    return false;
}

//Block 2, Preliminary Correcting File Format
void NorminetteCorrector::preliminaryCorrectingFileFormat()
{
    bracesMustBeOnNewLine();
    afterSemicolonMustBeEmpty();
    unnecessarySpaces();
    deleteBlankLines();
}
void NorminetteCorrector::bracesMustBeOnNewLine()
{
    for (ushint start = m_startLine; start < size(); ++start)
    {
        int index = -1;
        std::string line = FileEditor::getLineIndex(start);

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
    for (ushint start = m_startLine; start < size(); ++start)
    {
        std::string line = FileEditor::getLineIndex(start);
        int index = searchSymbolsInLine(line, ";");
        
        if (index < 0)
            continue;

        int indexEnd = FileEditor::getIndexLineEnd(start) - 1;
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
        reservData = FileEditor::separateBySpaces(start);

        if (reservData.empty())
        {
            FileEditor::setLineIndex(start, "");
            continue;
        }

        std::string newLine = reservData[0];
        for (ushint index = 1; index < reservData.size(); ++index)
        {
            newLine += " " + reservData[index];
        }
        FileEditor::setLineIndex(start, newLine);
    }
}
void NorminetteCorrector::deleteBlankLines()
{
    for (ushint start = m_startLine; start < size(); ++start)
    {
        std::string line = FileEditor::getLineIndex(start);
        
        if (line.empty())
        {
            FileEditor::deleteLineIndex(start);
            --start;
        }
    }
}
//void NorminetteCorrector::correctTabulations()
//{
//    //correctBrackets
//}
//void NorminetteCorrector::correctBrackets()
//{
//
//}

//Block 3, correct Inside Line
void NorminetteCorrector::correctInsideLine()
{
    createMemberText();


    //skzbunq, 
    //Stroev grnac metodnery chpetq a poxen m_data-n u bun texty 
    //menak karan poxen line-ery, 
    //line-ery popoxelov berum enq verjnakan tesqi
    //vorn el verjum  poxum a m_data-yi parunakutyuny.

    correctSemicolon();
    correctIfWhileElse();
    correctReturns();

    updateBracesText();


    correctInitialization();
}

void NorminetteCorrector::createMemberText()
{
    for (ushint start = m_startLine; start < size(); ++start)
    {
        std::vector<std::string> line = separateByKeySymbols(start);
        m_text.push_back(line);
    }
}
std::vector<std::string> NorminetteCorrector::separateByKeySymbols(ushint lineStart)
{
    std::vector<std::string> words = FileEditor::separateBySpaces(lineStart);
    std::vector<std::string> newWords;
    ushint size = static_cast<ushint>(words.size());
    for (ushint start = 0; start < size; ++start)
    {
        std::string Words = words[start];
        std::string word = "";
        for (ushint index = 0; index < Words.size(); ++index)
        {

            const char symbol = Words[index];

            if (symbol == ',')
                std::cout << "";

            if (!std::isalpha(symbol) && !std::isdigit(symbol) && symbol != '_')
            {
                if (word.empty())
                {
                    word += symbol;
                    newWords.push_back(word);
                    word = "";
                    continue;
                }
                
                newWords.push_back(word);
                

                if (!std::isspace(symbol))
                {
                    word = symbol;
                    newWords.push_back(word);
                    word = "";
                }
                else
                {
                    word = "";
                }
            }
            else
            {
                word += symbol;
            }
        }
        if (word.empty())
            continue;
        newWords.push_back(word);
    }

    words = newWords;
    return words;
}

bool NorminetteCorrector::searchInWords(const std::vector<std::string>& words, const std::string& keyWord)
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
void NorminetteCorrector::addNewLineInTextIndex(const unsigned short indexLine,const std::vector<std::string>& newLine)
{
    std::vector<std::string> Line = newLine;
    ushint size = static_cast<ushint>(m_text.size());

    for (unsigned short int index = indexLine; index < size; ++index)
    {
        std::vector<std::string> registerLine = m_text[index];
        m_text[index] = Line;
        Line = registerLine;
    }
    m_text.push_back(Line);

    if (m_BracesIndex.empty())
        return;
    updateBracesAddNewLine(indexLine);
}
void NorminetteCorrector::deleteLineInTextIndex(const unsigned short indexLine)
{
    for (unsigned short int index = indexLine; index < m_text.size() - 1; ++index)
    {
        m_text[index] = m_text[index + 1];
    }
    m_text.pop_back();
    
    if (m_BracesIndex.empty())
        return;
    updateBracesDeleteLine(indexLine);
}
void NorminetteCorrector::updata()
{
    ushint cycles = std::min((int)m_text.size(), size() - m_startLine);

    for (ushint indexLine = 0; indexLine < cycles; ++indexLine)
    {
        std::vector<std::string>& line = m_text[indexLine];

        std::string newline;

        if (line.empty())
            continue;

        newline += line[0];
        for (ushint index = 1; index < line.size(); ++index)
        {
            newline += " " + line[index];
        }
        FileEditor::setLineIndex(indexLine + m_startLine, newline);
    }
    if ((int)m_text.size() > size() - m_startLine)
    {
        for (ushint start = cycles; start < m_text.size(); ++start)
        {
            std::vector<std::string>& line = m_text[start];

            std::string newline;

            if (line.empty())
                continue;

            newline += line[0];
            for (ushint index = 1; index < line.size(); ++index)
            {
                newline += " " + line[index];
            }
            FileEditor::addNewLineBack(newline);
        }
    }
    else if ((int)m_text.size() < size() - m_startLine)
    {
        for (ushint indexLine = cycles; indexLine < size(); ++indexLine)
        {
            FileEditor::deleteLineBack();
        }
    }
    else
    {
        return;
    }


}

void NorminetteCorrector::correctSemicolon()
{
    if (m_text.empty())
        return;
    for (ushint indexLine = 0; indexLine < m_text.size(); ++indexLine)
    {
        if (m_text[indexLine].size() == 1 && m_text[indexLine][0] == ";")
        {
            aloneSemicolonRaiseUp(indexLine);
        }
        deleteUnnecessarySemicolon(indexLine);
        //beforeSemicolonShouldBeNoSpace(indexLine, text);
    }
}
void NorminetteCorrector::aloneSemicolonRaiseUp(ushint& indexLine)
{
    if (indexLine == 9)
        std::cout;
    m_text[indexLine - 1].back() = m_text[indexLine - 1].back() + ";";
    
    for (ushint start = indexLine; start < m_text.size() - 1; ++start)
    {
        m_text[start] = m_text[start + 1];
    }
    m_text.pop_back();

    --indexLine;
}
void NorminetteCorrector::deleteUnnecessarySemicolon(ushint& indexLine)
{
    std::string line = m_text[indexLine].back();

    if (line.empty() || line.size() == 1 || line.back() != ';')
        return;
    for (shint index = static_cast<shint>(line.size()) - 2; index >= 0; --index)
    {
        if (line[index] == ';')
            line.pop_back();
    }

    m_text[indexLine].back() = line;
}
void NorminetteCorrector::beforeSemicolonShouldBeNoSpace(ushint& indexLine)
{
    std::vector <std::string> line = m_text[indexLine];

    int indexLineEnd = static_cast<int>(line.size()) - 1;

    if (indexLineEnd == 0 || line[indexLineEnd] != ";")
        return;

    line[indexLineEnd - 1] += line[indexLineEnd];
    line.pop_back();
    m_text[indexLine] = line;

}

void NorminetteCorrector::correctIfWhileElse()
{
    for (ushint indexLine = 0; indexLine < m_text.size(); ++indexLine)
    {
        correctIf(indexLine);
        correctWhile(indexLine);
        correctElse(indexLine);
    }
}
void NorminetteCorrector::correctIf(ushint& indexLine)
{
    //after if should be no space

    std::vector<std::string>& line = m_text[indexLine];
    const std::string keyWord = "if";

    if (!searchInWords(line, keyWord))
    {
        return;
    }

    ushint start = 0;
    while (line[start] != keyWord && start < line.size())
        ++start;
    ++start;

    shint count = 0;

    for (; start < line.size(); ++start)
    {
        if (line[start] == "(")
            ++count;
        else if (line[start] == ")")
            --count;
        if (count == 0)
            break;
    }

    if (start == line.size() - 1)
        return;

    std::vector<std::string> newData;

    for (ushint index = start + 1; index < line.size(); ++index)
    {
        newData.push_back(line[index]);
    }

    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start; --index)
    {
        line.pop_back();
    }

    addNewLineInTextIndex(indexLine + 1, newData);

    //std::vector<std::string> forNotError;
    //forNotError[0] = "{";
    ////addNewLineInTextIndex(indexLine + 1, text, "{");
    //addNewLineInTextIndex(indexLine + 1, text, forNotError);
    //addNewLineInTextIndex(indexLine + 2, text, newData);
    ////addNewLineInTextIndex(indexLine + 3, text, "}");
    //forNotError[0] = "}";
    //addNewLineInTextIndex(indexLine + 3, text, forNotError);
}
void NorminetteCorrector::correctWhile(ushint& indexLine)
{
    //after while should be no space

    std::vector<std::string>& line = m_text[indexLine];
    const std::string keyWord = "while";

    if (!searchInWords(line, keyWord))
    {
        return;
    }

    ushint start = 0;
    while (line[start] != keyWord && start < line.size())
        ++start;
    ++start;

    shint count = 0;

    for (; start < line.size(); ++start)
    {
        if (line[start] == "(")
            ++count;
        else if (line[start] == ")")
            --count;
        if (count == 0)
            break;
    }

    if (start == line.size() - 1)
        return;

    std::vector<std::string> newData;

    for (ushint index = start + 1; index < line.size(); ++index)
    {
        newData.push_back(line[index]);
    }

    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start; --index)
    {
        line.pop_back();
    }

    addNewLineInTextIndex(indexLine + 1, newData);
}
void NorminetteCorrector::correctElse(ushint& indexLine)
{
    //after else should be no space

    std::vector<std::string>& line = m_text[indexLine];
    const std::string keyWord = "else";

    if (!searchInWords(line, keyWord))
    {
        return;
    }

    if (line.size() < 2)
        return;

    ushint start = 0;
    while (line[start] != keyWord && start < line.size())
        ++start;
    ++start;

    if (start == line.size() - 1)
        return;

    if (line[start] == "if")
        return;

    std::vector<std::string> newData;

    for (ushint index = start; index < line.size(); ++index)
    {
        newData.push_back(line[index]);
    }

    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start - 1; --index)
    {
        line.pop_back();
    }

    addNewLineInTextIndex(indexLine + 1, newData);
}

void NorminetteCorrector::correctReturns()
{
    for (ushint indexLine = 0; indexLine < m_text.size(); ++indexLine)
    {
        std::vector<std::string>& line = m_text[indexLine];

        const std::string keyWord = "return";

        if (line.size() < 3 || !searchInWords(line, keyWord))
            continue;

        //for testing, not for relise
        assert(line.front() == keyWord && "Whil be a return");

        if (line[1] == "(")
            continue;

        std::vector<std::string> data;

        data.push_back(line.front());
        data.push_back("(");

        for (ushint index = 1; index < line.size() - 1; ++index)
        {
            data.push_back(line[index]);
        }

        data.push_back(")");
        data.push_back(line.back());

        line = data;
    }

}

//for work whit braces
//void NorminetteCorrector::updateBraces()
//{
//    m_BracesIndex.clear();
//
//    unsigned short countBracesStart = 0;
//    unsigned short countBracesEnd = 0;
//    unsigned short indexForBracesArr = -1;
//
//    for (ushint start = m_startLine; start < size(); ++start)
//    {
//        const char symbol = FileEditor::getLineIndex(start)[0];
//        ushint count = 0;
//
//        if (symbol == '{')
//        {
//            if (countBracesStart == countBracesEnd)
//            {
//                ++indexForBracesArr;
//                m_BracesIndex.resize(indexForBracesArr + 1);
//            }
//            m_BracesIndex[indexForBracesArr].push_back(start);
//            ++countBracesStart;
//        }
//        if (symbol == '}')
//        {
//            m_BracesIndex[indexForBracesArr].push_back(-start);
//            ++countBracesEnd;
//        }
//    }
//    m_BracesIndex.shrink_to_fit();
//}
//void NorminetteCorrector::updateBracesInAllData()
//{
//    m_BracesIndex.clear();
//
//    unsigned short countBracesStart = 0;
//    unsigned short countBracesEnd = 0;
//    unsigned short indexForBracesArr = -1;
//
//    for (unsigned short start = m_startLine; start < size(); ++start)
//    {
//        std::string line = FileEditor::getLineIndex(start);
//        for (unsigned short index = 0; index < line.size(); ++index)
//        {
//            char c = line[index];
//            if (c == '{')
//            {
//                if (countBracesStart == countBracesEnd)
//                {
//                    ++indexForBracesArr;
//                    m_BracesIndex.resize(indexForBracesArr + 1);
//                }
//                m_BracesIndex[indexForBracesArr].push_back(start);
//                ++countBracesStart;
//            }
//            if (c == '}')
//            {
//                m_BracesIndex[indexForBracesArr].push_back(-start);
//                ++countBracesEnd;
//
//            }
//        }
//    }
//    m_BracesIndex.shrink_to_fit();
//}
void  NorminetteCorrector::  updateBracesText( )
{
    if (m_text.empty())
    {
        std::cout << "Text is empty" << std::endl;
        return;
    }

    m_BracesIndex.clear();

    unsigned short countBracesStart = 0;
    unsigned short countBracesEnd = 0;
    unsigned short indexForBracesArr = -1;

    for (ushint start = 0; start < m_text.size(); ++start)
    {
        const std::string symbol = m_text[start][0];
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
void  NorminetteCorrector::  printBraces()
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
            std::cout <<  indexLine << ' ';
        }
        std::cout << std::endl;
    }
}
void  NorminetteCorrector::  printBracesForText()
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
void  NorminetteCorrector::  updateBracesAddNewLine(ushint indexDeleteLine)
{
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
int   NorminetteCorrector::  getPositive(int index)
{
    if (index >= 0)
        return index;
    else
        return -index;
}
void  NorminetteCorrector::  updateBracesDeleteLine(ushint indexDeleteLine)
{
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
shint NorminetteCorrector::  getFunctionStartIndex(ushint indexInFunctionBody)
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
shint NorminetteCorrector::  getFunctionEndIndex(ushint indexInFunctionBody)
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
//shint NorminetteCorrector::returnFunctionStartIndex(ushint indexInFunctionBody)
//{
//
//}

//For initilization member data
void NorminetteCorrector::   initVaribleKeyWords()
{
    if (!m_varibleKeyWords.empty())
    {
        m_varibleKeyWords.clear();
    }


    m_varibleKeyWords.reserve(9);

    m_varibleKeyWords.push_back("short");
    m_varibleKeyWords.push_back("ushort");
    m_varibleKeyWords.push_back("ushint");
    m_varibleKeyWords.push_back("int");
    m_varibleKeyWords.push_back("uint");
    m_varibleKeyWords.push_back("long");
    m_varibleKeyWords.push_back("ulong");
    m_varibleKeyWords.push_back("float");
    m_varibleKeyWords.push_back("double");

    assert(m_varibleKeyWords.size() == 9 && "size whil be 9");
}
void NorminetteCorrector::   addNewVaribleKeyWords(std::string keyWord)
{
    m_varibleKeyWords.push_back(keyWord);
}
//void NorminetteCorrector::deleteVaribleKeyWords(std::string keyWord)
//{
//    for()
//    m_varibleKeyWords.push_back(keyWord);
//}

void NorminetteCorrector::   correctInitialization()
{
    if (m_BracesIndex.empty())
        updateBracesText();

    if (m_BracesIndex.empty())
        return;

    if (m_varibleKeyWords.empty())
        initVaribleKeyWords();

    printText();
    printBracesForText();

    //for test
    ushint size = static_cast<ushint>(m_BracesIndex.size());

    for (ushint start = 0; start < size; ++start)
    {
        if (start == 4)
        {
            printText();
            printBracesForText();
        }
        correctInitializationInFunction(m_BracesIndex[start].front() + 1, -m_BracesIndex[start].back() - 1);
    }

    m_varibleKeyWords.clear();
}
void NorminetteCorrector::   correctInitializationInFunction(int indexStartFunction, int indexEndFunction)
{
    if (indexStartFunction < 0 || indexEndFunction < 0)
    {
        std::cerr << "arguments is negative" << std::endl;
        std::cout << "indexStartFunction = " << indexStartFunction << std::endl;
        std::cout << "indexEndFunction = "   << indexEndFunction   << std::endl;
        return;
    }

    ushint startDeclaration = searchDeclarationStartInFunctionIndex(indexStartFunction, indexEndFunction);
    
    //for test
    std::cout << "Function start = " << indexStartFunction << "  " << "Function End = " << indexEndFunction << std::endl;
    std::cout << startDeclaration << std::endl;


    for (ushint start = startDeclaration; start <= NorminetteCorrector::getFunctionEndIndex(start); ++start)
    {
        if (!isThereDeclarationInTextLine(start)) 
        {
            continue;
        }
        if (isThereAssignmentInTextLine(start))
        {
            separateDeclarationFromAssignment(startDeclaration, start);
        }
        else
        {
            raiseDeclarationUp(startDeclaration, start);
        }
        std::cout << "Init line index :: " << start << std::endl;
    }
}
ushint NorminetteCorrector:: searchDeclarationStartInFunctionIndex(int indexStartFunction, int indexEndFunction)
{
    if (m_text.size() == 1 && m_text[indexStartFunction].front() == "{")
    {
        ++indexStartFunction;
    }
    if (m_text.size() == 1 && m_text[indexStartFunction].front() == "}")
    {
        --indexEndFunction;
    }

    if (indexStartFunction < 0 || indexEndFunction < 0)
    {
        std::cerr << "arguments is negative" << std::endl;
        std::cout << "indexStartFunction = " << indexStartFunction << std::endl;
        std::cout << "indexEndFunction = " << indexEndFunction << std::endl;
        return (0);
    }

    for (ushint indexLine = indexStartFunction; indexLine < getFunctionEndIndex(indexLine); ++indexLine)
    {
        if (!isThereDeclarationInTextLine(indexLine))
        {
            return (indexLine);
        }
        else
        {
            if (isThereAssignmentInTextLine(indexLine))
            {
                return (indexLine);
            }
        }
    }

    return (indexStartFunction + 1);
}
bool NorminetteCorrector::   isThereDeclarationInTextLine(ushint indexLine)
{
    std::vector<std::string> line = m_text[indexLine];

    if (m_varibleKeyWords.empty())
    {
        NorminetteCorrector::initVaribleKeyWords();
    }

    for (ushint start = 0; start < line.size(); ++start)
    {
        for (ushint index = 0; index < m_varibleKeyWords.size(); ++index)
        {
            if (searchInWords(line, m_varibleKeyWords[index]))
            {
                return true;
            }
        }
    }
    return false;
}
bool NorminetteCorrector::   isThereAssignmentInTextLine(ushint indexLine)
{
    std::vector<std::string> line = m_text[indexLine];

    for (shint start = static_cast<shint>(line.size() - 1); start >= 0; --start)
    {
        if (line[start] == "=")
        {
            return true;
        }
    }
    return false;
}
void NorminetteCorrector::   separateDeclarationFromAssignment(ushint& startDeclaration, ushint indexLine)
{
    std::vector<std::string> line = m_text[indexLine];

    std::vector<std::string> newLine;

    ushint start = 0;
    for (; start < line.size(); ++start)
    {
        if (line[start] == "=")
        {
            break;
        }
        newLine.push_back(line[start]);
    }
    newLine.push_back(";");
    NorminetteCorrector::addNewLineInTextIndex(startDeclaration, newLine);
    ++startDeclaration;

    newLine.clear();

    newLine.push_back(line[start - 1]);

    for (; start < line.size(); ++start)
    {
        newLine.push_back(line[start]);
    }

    m_text[indexLine + 1] = newLine;
}
void NorminetteCorrector::   raiseDeclarationUp(ushint& startDeclaration, ushint& indexLine)
{
    std::vector<std::string> line = m_text[indexLine];

    NorminetteCorrector::deleteLineInTextIndex(indexLine);

    NorminetteCorrector::addNewLineInTextIndex(startDeclaration, line);
    ++startDeclaration;
    --indexLine;
}
//bool NorminetteCorrector::isThereInitializationInTextLine(ushint indexLine)
//{
//
//}

//Block 4, to finalize
void NorminetteCorrector::correctForFinalize()
{
    correctFunctionName();
    deleteUnnecessarySpaceSemicolon();
    correctFunctionBody();
}

bool NorminetteCorrector::isBracesIndex(int indexLine)
{
    //test
    assert(indexLine > 0 && "Index shell be positive");

    if (indexLine <= 0)
    {
        return false;
    }

    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        for (ushint index = 0; index < m_BracesIndex[start].size(); ++index)
        {
            int bracesIndex = NorminetteCorrector::getPositive(m_BracesIndex[start][index]);

            if (indexLine == bracesIndex)
            {
                return true;
            }
        }
    }

    return false;
}

void NorminetteCorrector::correctFunctionName()
{
    for (ushint start = 0; start < static_cast<ushint>(m_BracesIndex.size()); ++start)
    {
        std::vector<std::string>& line = m_text[m_BracesIndex[start][0] - 1];

        deleteUnnecessarySpaceInFunctionName(line);
    }
}
void NorminetteCorrector::deleteUnnecessarySpaceSemicolon()
{
    for (ushint start = 0; start < m_text.size(); ++start)
    {
        std::vector<std::string>& line = m_text[start];

        if (line.back() == ";")
        {
            line[line.size() - 2] += ";";
            line.pop_back();
        }
    }
}
void NorminetteCorrector::deleteUnnecessarySpaceMathOperators()
{

}
void NorminetteCorrector::deleteUnnecessarySpaceInFunctionName(std::vector<std::string>& line)
{
    shint size = static_cast<shint>(line.size());

    //for test
    assert(size && "line chpetq a lini 0");


    if (size == 0 || size == 1)
    {
        return;
    }

    std::string result = line[0];

    for (ushint index = 1; index < line.size(); ++index)
    {
        char symbol = line[index][0];
        

        if (std::isalpha(symbol))
        {
            result += " " + line[index];
        }
        else if (symbol == '(')
        {
            result += line[index];
            ++index;
            result += line[index];
        }
        else
        {
            result += line[index];
        }
    }

    line.clear();
    line.push_back(result);
}
void NorminetteCorrector::correctFunctionBody()
{
    for (ushint start = 0; start < static_cast<ushint>(m_BracesIndex.size()); ++start)
    {
        int indexStartFunction = m_BracesIndex[start][0] + 1;
        int indexEndFunction = -m_BracesIndex[start].back() - 1;


        const ushint startLine = searchDeclarationStartInFunctionIndex(indexStartFunction, indexEndFunction);

        for (ushint index = indexStartFunction; index < startLine; ++index)
        {
            //delete unnecessary space in declaration

            std::vector<std::string>& line = m_text[index];

            deleteUnnecessarySpaceInDeclaration(line);
        }

        for (ushint index = startLine; index < indexEndFunction; ++index)
        {
            if (isBracesIndex(index))
            {
                continue;
            }

            std::vector<std::string>& line = m_text[index];

            const std::string keyWordIf = "if";
            const std::string keyWordWhile = "while";


            if (searchInWords(line, keyWordIf) || searchInWords(line, keyWordWhile))
            {
                //delete unnecessary space in if and While
                //deleteUnnecessarySpaceInIfAndWhile(line);

                continue;
            }

            //correct line
        }
    }

    
}
void NorminetteCorrector::deleteUnnecessarySpaceInDeclaration(std::vector<std::string>& line)
{
    shint size = static_cast<shint>(line.size());

    //for test
    assert(size && "line chpetq a lini 0");


    if (size == 0 || size == 1)
    {
        return;
    }

    std::string result = line[0];

    for (ushint index = 1; index < line.size(); ++index)
    {
        char symbol = line[index][0];


        if (std::isalpha(symbol))
        {
            result += " " + line[index];
        }
        else if (symbol == '[')
        {
            result += line[index];
            ++index;
            result += line[index];
        }
        else
        {
            result += line[index];
        }
    }

    line.clear();
    line.push_back(result);
}
void NorminetteCorrector::deleteUnnecessarySpaceInIfAndWhile(std::vector<std::string>& line)
{
    shint size = static_cast<shint>(line.size());

    //for test
    assert(size && "line chpetq a lini 0");


    if (size == 0 || size == 1)
    {
        return;
    }

    std::string result = line[0];

    for (ushint index = 1; index < line.size(); ++index)
    {
        char symbol = line[index][0];

        if (symbol == '(')
        {
            result += " " + line[index];
            ++index;
            result += line[index];
        }
        else if(symbol == '&' || symbol == '|')
        {

        }
        else if (true)
        {

        }
        if (std::isalpha(symbol))
        {
            result += " " + line[index];
        }
        //else if (symbol == '(')
        //{
        //    result += line[index];
        //    ++index;
        //    result += line[index];
        //}
        else
        {
            result += line[index];
        }
    }

    line.clear();
    line.push_back(result);
}