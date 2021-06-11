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
bool NorminetteCorrector::isdigit(const std::string& word) const
{
    if (word.empty())
        return (false);

    for (ushint index = 0; index < word.size(); ++index)
    {
        const char symbol = word[index];
        if (!std::isdigit(symbol))
        {
            return (false);
        }
    }

    return (true);
}
bool NorminetteCorrector::isalpha(const std::string& word) const
{
    for (ushint index = 0; index < word.size(); ++index)
    {
        if (!std::isalpha(word[index]))
        {
            return false;
        }
    }
    return true;
}
bool NorminetteCorrector::isTabulation(const std::string& word)
{
    if (word.empty())
        return false;
    for (ushint index = 0; index < word.size(); ++index)
    {
        if (word[index] != '\t')
            return false;
    }
    return true;
}
std::string NorminetteCorrector::getOldFileName()
{
    std::string fileRoad = getFileName();
    std::string reservFileName = "";
    std::string newName = "";

    shint index = static_cast<shint>(fileRoad.size()) - 1;
    for (; index >= 0; --index)
    {
        if (fileRoad[index] == '/')
        {
            break;
        }
        reservFileName.push_back(fileRoad[index]);
        fileRoad.pop_back();
    }
    newName = fileRoad + "old_";

    for (shint index = static_cast<shint>(reservFileName.size()) - 1; index >= 0; --index)
    {
        newName += reservFileName[index];
    }

    return (newName);
}
std::string NorminetteCorrector::getNewFileName()
{
    std::string fileRoad = getFileName();
    std::string reservFileName = "";
    std::string newName = "";

    shint index = static_cast<shint>(fileRoad.size()) - 1;
    for (; index >= 0; --index)
    {
        if (fileRoad[index] == '/')
        {
            break;
        }
        reservFileName.push_back(fileRoad[index]);
        fileRoad.pop_back();
    }
    newName = fileRoad + "new_";

    for (shint index = static_cast<shint>(reservFileName.size()) - 1; index >= 0; --index)
    {
        newName += reservFileName[index];
    }

    return (newName);
}
//void NorminetteCorrector::                    combineWords(ushint indexLine, ushint& indexLeftWord, ushint indexRightWord)
//{
//    FileTextEditor::combineWords(indexLine, indexLeftWord, indexRightWord);
//    //if(indexLeftWord > 1)
//    //    --indexLeftWord;
//}
void NorminetteCorrector::                    addNewLine(int indexLine, const std::vector<std::string>& newLine)
{
    FileTextEditor::addNewLine(indexLine, newLine);
    NorminetteCorrector::updateBracesAddNewLine(indexLine);
}
void NorminetteCorrector::                    addNewLine(int indexLine, const std::string& newLine)
{
    FileTextEditor::addNewLine(indexLine, newLine);
    NorminetteCorrector::updateBracesAddNewLine(indexLine);
}
void NorminetteCorrector::                    deleteLine(int indexLine)
{
    FileTextEditor::deleteLine(indexLine);
    NorminetteCorrector::updateBracesDeleteLine(indexLine);
}

void NorminetteCorrector::                    addNewLineBack(const std::vector<std::string>& newLine)
{
    FileTextEditor::addNewLineBack(newLine);
    NorminetteCorrector::updateBracesAddNewLine(FileTextEditor::size() - 2);
}
void NorminetteCorrector::                    addNewLineBack(std::string& newLine)
{
    FileTextEditor::addNewLineBack(newLine);
    NorminetteCorrector::updateBracesAddNewLine(FileTextEditor::size() - 2);
}
void NorminetteCorrector::                    deleteLineBack()
{
    FileTextEditor::deleteLineBack();
    NorminetteCorrector::updateBracesDeleteLine(FileTextEditor::size());
}

void NorminetteCorrector::updata()
{
    for (ushint start = 0; start < size(); ++start)
    {
        std::vector<std::string>& line = FileTextEditor::getLine(start);

        if (line.empty())
        {
            FileEditor::setLine(start, "");
            continue;
        }

        std::string newLine = line.front();

        for (ushint index = 1; index < line.size() - 1; ++index)
        {
            if (isTabulation(line[index]))
            {
                newLine += line[index];
            }
            else if (isTabulation(line[(int)index + 1]))
            {
                newLine += line[index];
            }
            else
            {
                newLine += line[index] + " "; 
            }
        }
        if (line.size() > 1)
            newLine += line.back();

        FileEditor::addNewLineBack(newLine);
    }

    FileTextEditor::clear();
}


//For corrector
void NorminetteCorrector::correctAll()
{
    if(FileEditor::getLine(FileEditor::size()-1).empty())
        FileEditor::deleteLineBack();
    //FileEditor::updateFile(NorminetteCorrector::getOldFileName());

    if (FileEditor::empty())
        return;

    if (!chackBasic())
    {
        std::cout << "Basic chack return false = error" << std::endl;
        return;
    }

    preliminaryCorrectingFileFormat();
    //FileEditor::print();

    FileTextEditor::init(m_startLine, FileEditor::size());
    //FileTextEditor::print();

    correctInsideLine();

    correctForFinalize();
    //FileTextEditor::print();
    //NorminetteCorrector::printBraces();

    NorminetteCorrector::updata();
    //FileEditor::print();
    //FileEditor::updateFile(FileEditor::getFileName());
    FileEditor::updateFile(NorminetteCorrector::getNewFileName());
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
    ushint endLine = FileEditor::size();

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
    for (ushint start = m_startLine; start < FileEditor::size(); ++start)
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
    correctSemicolon();
    correctIfWhileElse();
    correctReturns();
    updateBraces();
    correctInitialization();
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

        if (symbol == '\"' || symbol == '\'')
        {
            separateStringInLine(word, newWords, index);
            continue;
        }

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
void NorminetteCorrector::separateStringInLine(const std::string& word, std::vector<std::string>& words, ushint& index)
{
    const char symbol = word[index];
    std::string newWord = "";

    newWord += word[index];
    ++index;
    for (; index < word.size(); ++index)
    {
        newWord += word[index];
        if (symbol == word[index])
        {
            break;
        }
    }
    words.push_back(newWord);
}

void NorminetteCorrector::correctSemicolon()
{
    if (FileTextEditor::empty())
        return;
    for (ushint indexLine = 0; indexLine < FileTextEditor::size(); ++indexLine)
    {
        if (FileTextEditor::getLine(indexLine).size() == 1 && FileTextEditor::getLine(indexLine)[0] == ";")
        {
            aloneSemicolonRaiseUp(indexLine);
        }
        deleteUnnecessarySemicolon(indexLine);
    }
}
void NorminetteCorrector::aloneSemicolonRaiseUp(ushint& indexLine)
{
    std::vector<std::string>& newLine = FileTextEditor::getLine(indexLine - 1);
    newLine.push_back(";");
    FileTextEditor::deleteLine(indexLine);

    --indexLine;
}
void NorminetteCorrector::deleteUnnecessarySemicolon(ushint& indexLine)
{
    std::vector<std::string>& line = FileTextEditor::getLine(indexLine);

    if (line.empty() || line.size() == 1 || line.back() != ";")
        return;

    for (shint index = static_cast<shint>(line.size()) - 2; index >= 0; --index)
    {
        if (line[index] == ";")
            line.pop_back();
    }
}

void NorminetteCorrector::correctIfWhileElse()
{
    for (ushint indexLine = 0; indexLine < FileTextEditor::size(); ++indexLine)
    {
        correctIf(indexLine);
        correctWhile(indexLine);
        correctElse(indexLine);
    }
}
void NorminetteCorrector::correctIf(ushint& indexLine)
{
    //after "if" should be no space

    std::vector<std::string> line = FileTextEditor::getLine(indexLine);
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

    std::vector<std::string> newLine;

    for (ushint index = start + 1; index < line.size(); ++index)
    {
        newLine.push_back(line[index]);
    }

    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start; --index)
    {
        line.pop_back();
    }

    setLine(indexLine, line);
    addNewLine(indexLine + 1, newLine);
}
void NorminetteCorrector::correctWhile(ushint& indexLine)
{
    //after while should be no space

    std::vector<std::string> line = FileTextEditor::getLine(indexLine);
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

    std::vector<std::string> newLine;

    for (ushint index = start + 1; index < line.size(); ++index)
    {
        newLine.push_back(line[index]);
    }

    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start; --index)
    {
        line.pop_back();
    }

    setLine(indexLine, line);
    addNewLine(indexLine + 1, newLine);
}
void NorminetteCorrector::correctElse(ushint& indexLine)
{
    //after else should be no space

    std::vector<std::string> line = FileTextEditor::getLine(indexLine);
    const std::string keyWord = "else";

    if (line.size() < 2)
        return;

    if (!searchInWords(line, keyWord))
    {
        return;
    }

    ushint start = 0;
    while (line[start] != keyWord && start < line.size())
        ++start;
    ++start;

    if (start == line.size() - 1)
        return;

    if (line[start] == "if")
        return;

    std::vector<std::string> newLine;

    for (ushint index = start; index < line.size(); ++index)
    {
        newLine.push_back(line[index]);
    }

    for (ushint index = static_cast<ushint>(line.size()) - 1; index > start - 1; --index)
    {
        line.pop_back();
    }

    setLine(indexLine, line);
    addNewLine(indexLine + 1, newLine);
}

void NorminetteCorrector::correctReturns()
{
    for (ushint indexLine = 0; indexLine < FileTextEditor::size(); ++indexLine)
    {
        std::vector<std::string> line = FileTextEditor::getLine(indexLine);

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
        FileTextEditor::setLine(indexLine, line);
    }
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
       
        //ushint count = 0; NAYEL
        if (symbol == "{")
        {
            if (countBracesStart == countBracesEnd)
            {
                ++indexForBracesArr;
                m_BracesIndex.resize((int)indexForBracesArr + 1);
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
            std::cout << NorminetteCorrector::getPositive(m_BracesIndex[start][index]) << ' ';
        }
        std::cout << std::endl;
    }
}
void  NorminetteCorrector::printBracesWhithHeader()
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
int   NorminetteCorrector::getPositive(int index) const
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

//For initilization member data
void NorminetteCorrector::initVaribleKeyWords(std::vector<std::string>& varibleKeyWords)
{
    if (!varibleKeyWords.empty())
    {
        varibleKeyWords.clear();
    }


    varibleKeyWords.reserve(12);

    varibleKeyWords.push_back("short");
    varibleKeyWords.push_back("ushort");
    varibleKeyWords.push_back("ushint");
    varibleKeyWords.push_back("int");
    varibleKeyWords.push_back("uint");
    varibleKeyWords.push_back("long");
    varibleKeyWords.push_back("ulong");
    varibleKeyWords.push_back("float");
    varibleKeyWords.push_back("double");
    varibleKeyWords.push_back("void");
    varibleKeyWords.push_back("char");
    varibleKeyWords.push_back("bool");
    varibleKeyWords.push_back("size_t");
    //varibleKeyWords.push_back("unsigned int");
}
void NorminetteCorrector::addNewVaribleKeyWords(std::vector<std::string>& varibleKeyWords, std::string keyWord)
{
    varibleKeyWords.push_back(keyWord);
}

void NorminetteCorrector::correctInitialization()
{
    if (m_BracesIndex.empty())
        updateBraces();

    if (m_BracesIndex.empty())
        return;

    for (ushint start = 0; start < static_cast<ushint>(m_BracesIndex.size()); ++start)
    {
        correctInitializationInFunction(m_BracesIndex[start].front() + 1, -m_BracesIndex[start].back() - 1);
    }
}
void NorminetteCorrector::correctInitializationInFunction(int indexStartFunction, int indexEndFunction)
{
    if (indexStartFunction < 0 || indexEndFunction < 0)
    {
        std::cerr << "arguments is negative" << std::endl;
        std::cout << "indexStartFunction = " << indexStartFunction << std::endl;
        std::cout << "indexEndFunction = " << indexEndFunction << std::endl;
        return;
    }

    ushint startDeclaration = searchDeclarationStartInFunction(indexStartFunction, indexEndFunction);

    for (ushint start = startDeclaration; start <= NorminetteCorrector::getFunctionEnd(start); ++start)
    {
        if (!isThereDeclarationInLine(start))
        {
            continue;
        }
        if (isThereAssignmentInLine(start))
        {
            separateDeclarationFromAssignment(startDeclaration, start);
        }
        else
        {
            raiseDeclarationUp(startDeclaration, start);
        }
    }
}
ushint NorminetteCorrector::searchDeclarationStartInFunction(int indexStartFunction, int indexEndFunction)
{
    std::string wordStart = FileTextEditor::getLine(indexStartFunction).front();
    std::string wordEnd = FileTextEditor::getLine(indexEndFunction).front();

    if (wordStart == "{")
    {
        ++indexStartFunction;
    }
    if (wordEnd == "}")
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

    for (ushint indexLine = indexStartFunction; indexLine < getFunctionEnd(indexLine); ++indexLine)
    {
        if (!isThereDeclarationInLine(indexLine))
        {
            return (indexLine);
        }
        else
        {
            if (isThereAssignmentInLine(indexLine))
            {
                return (indexLine);
            }
        }
    }

    return (indexStartFunction);
}
bool NorminetteCorrector::isThereDeclarationInLine(ushint indexLine)
{
    const std::vector<std::string>& line = getLine(indexLine);

    for (ushint start = 0; start < line.size(); ++start)
    {
        if (NorminetteCorrector::isWordDeclarationKeyWord(line[start]))
        {
            bool key = true;
            for (shint index = start - 1; index >= 0; --index)
            {
                if (!NorminetteCorrector::isalpha(line[index]))
                {
                    key = false;
                    break;
                }
            }
            return key;
        }
    }
    return false;
}
bool NorminetteCorrector::isThereAssignmentInLine(ushint indexLine)
{
    const std::vector<std::string>& line = getLine(indexLine);

    for (shint start = static_cast<shint>(line.size() - 1); start >= 0; --start)
    {
        if (line[start] == "=")
        {
            return true;
        }
    }
    return false;
}
void NorminetteCorrector::separateDeclarationFromAssignment(ushint& startDeclaration, ushint indexLine)
{
    const std::vector<std::string> line = getLine(indexLine);
    std::vector<std::string> newLine;

    if (!NorminetteCorrector::isWordDeclarationKeyWord(line.front()))
    {
        if (isLineMalloc(line) || isLineCCast(line))
        {
            return;
        }
    }

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
    NorminetteCorrector::addNewLine(startDeclaration, newLine);
    ++startDeclaration;

    newLine.clear();

    newLine.push_back(line[start - 1]);

    for (; start < line.size(); ++start)
    {
        newLine.push_back(line[start]);
    }


    FileTextEditor::setLine(indexLine + 1, newLine);
}
bool NorminetteCorrector::isLineMalloc(const std::vector<std::string>& line)
{
    for (ushint index = 0; index < line.size(); ++index)
    {
        if (line[index] == "malloc")
            return true;
    }
    return false;
}
bool NorminetteCorrector::isLineCCast(const std::vector<std::string>& line)
{
    for (ushint start = 1; start < line.size(); ++start)
    {
        if (NorminetteCorrector::isWordDeclarationKeyWord(line[start]))
        {
            for (shint index = start; index >= 0; --index)
            {
                if (NorminetteCorrector::isalpha(line[index]))
                {
                    continue;
                }
                if (line[index] == "(")
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void NorminetteCorrector::raiseDeclarationUp(ushint& startDeclaration, ushint& indexLine)
{
    const std::vector<std::string>& line = getLine(indexLine);

    NorminetteCorrector::deleteLine(indexLine);

    NorminetteCorrector::addNewLine(startDeclaration, line);
    ++startDeclaration;
    --indexLine;
}
bool NorminetteCorrector::isWordDeclarationKeyWord(const std::string& word)
{
    std::vector<std::string> varibleKeyWords;
    NorminetteCorrector::initVaribleKeyWords(varibleKeyWords);
    NorminetteCorrector::initVaribleKeyWords(varibleKeyWords);


    if (word.size() < 3 || word.size() > 6 || !std::isalpha(word.front()))
        return false;

    for (ushint index = 0; index < varibleKeyWords.size(); ++index)
    {
        if (varibleKeyWords[index] == word)
        {
            return true;
        }
    }
    return false;
}

//CodeBlock 4, final corrections
void NorminetteCorrector::correctForFinalize()
{
    correctMathOperators();
    correctBrackets();
    beforeSemicolonShouldBeNoSpace();
    correctComma();
    correctTabulation();
    addFewerLines();
}

void NorminetteCorrector::correctMathOperators()
{
    //+,-,*,/,%,&,|,
    //++,--, postfix and prefix 
    //+=,-=,*=,/=,%=,
    //&&, ||

    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        ushint startFunction = m_BracesIndex[start].front();
        ushint endFunction   = -m_BracesIndex[start].back();
        correctMathOperatorsInFunction(startFunction - 1, endFunction);
    }
}
void NorminetteCorrector::correctMathOperatorsInFunction(ushint startFunction, ushint endFunction)
{
    for (ushint start = startFunction; start < endFunction; ++start)
    {
        if (start == 132)
            std::cout << "";
        searchMathOperatorsInLine(start);
    }
}
void NorminetteCorrector::searchMathOperatorsInLine(ushint indexLine)
{
    std::vector<std::string> words = FileTextEditor::getLine(indexLine);

    searchUnaryMathOperatorInLine(indexLine, words);
    searchBinaryMathOperatorInLine(indexLine, words);
}
void NorminetteCorrector::correctMathOperatorsInLine(ushint indexLine, ushint& indexWord)
{
    std::vector<std::string> line = FileTextEditor::getLine(indexLine);
    
    int indexEnd = indexWord + 1;
    if (line[(int)indexWord + 1] == "*" || line[(int)indexWord + 1] == "&")
    {
        indexEnd = latestMathOperatorIndex(indexLine, indexWord + 1);
    }

    FileTextEditor::combineWords(indexLine, indexWord, indexEnd);

    line = FileTextEditor::getLine(indexLine);
    if (isIncrementOrDecrement(line[indexWord]))
    {
        correctIncrementOrDecrement(indexLine, indexWord);
    }
    if (isPointerOrReferenceMathOperator(line[indexWord]))
    {
        if (line[indexWord] != "&&")
            FileTextEditor::combineWords(indexLine, indexWord, indexWord + 1);
    }
}
void NorminetteCorrector::searchUnaryMathOperatorInLine(ushint indexLine, std::vector<std::string>& words)
{
    for (ushint indexWord = 0; indexWord < words.size(); ++indexWord)
    {
        if (isUnaryMathOperator(indexLine, words, indexWord))
        {
            FileTextEditor::combineWords(indexLine, indexWord, indexWord + 1);
            words = FileTextEditor::getLine(indexLine);
        }
    }
}
void NorminetteCorrector::searchBinaryMathOperatorInLine(ushint indexLine, std::vector<std::string>& words)
{
    for (ushint indexWord = 0; indexWord < words.size(); ++indexWord)
    {
        if (isMathOperator(words[indexWord]))
        {
            if (isMathOperator(words[(int)indexWord + 1]))
            {
                correctMathOperatorsInLine(indexLine, indexWord);
                words = FileTextEditor::getLine(indexLine);
            }
            else if (isPointerMathOperator(words[indexWord]) or isReferenceMathOperator(words[indexWord]))
            {
                if (!isdigit(words[(int)indexWord + 1]))
                {
                    FileTextEditor::combineWords(indexLine, indexWord, indexWord + 1);
                    words = FileTextEditor::getLine(indexLine);
                }
            }
        }
    }
}
bool NorminetteCorrector::isFirstWordUnaryMathOperator(std::vector<std::string>& line)
{
    if (line.front().size() != 1)
        return false;

    return (isWordUnaryMathOperator(line.front()));
}
bool NorminetteCorrector::isUnaryMathOperator(ushint indexLine, std::vector<std::string>& words, ushint& indexWord)
{
    (void)indexLine;//NAYEL
    if (words[indexWord].size() != 1)
        return false;

    if (!isWordUnaryMathOperator(words[indexWord]))
    {
        return false;
    }

    if (isMathOperator(words[(int)indexWord + 1]))
    {
        return false;
    }

    if (indexWord == 0)
    {
        return (isFirstWordUnaryMathOperator(words));
    }

    const std::vector < std::string> keyWordsBeforeUnaryMathOperator{ "(", "[", "=" };

    for (ushint index = 0; index < keyWordsBeforeUnaryMathOperator.size(); ++index)
    {
        if (words[indexWord - 1] == keyWordsBeforeUnaryMathOperator[index])
        {
            return true;
        }
    }

    return false;
}
bool NorminetteCorrector::isWordUnaryMathOperator(const std::string& symbol)
{
    const std::vector<std::string>   keyWordsUnaryMathOperator{ "+", "-", "!" };

    for (ushint index = 0; index < keyWordsUnaryMathOperator.size(); ++index)
    {
        if (symbol == keyWordsUnaryMathOperator[index])
        {
            return true;
        }
    }
    return false;
}
bool NorminetteCorrector::isMathOperator(const std::string& word) const
{
    const std::vector<std::string> keyWords{ "+","-","*","/","%","&","|",
        "=", "!", "+=","-=","*=","/=","%=", "==", "!=", "<", ">", "<=",
        ">=", "<!", ">!", "<<", ">>"};

    for (ushint index = 0; index < keyWords.size(); ++index)
    {
        if (keyWords[index] == word)
        {
            return true;
        }
    }

    if (isPointerMathOperator(word) or isReferenceMathOperator(word))
    {
        return true;
    }

    return false;
}
bool NorminetteCorrector::isPointerOrReferenceMathOperator(const std::string& word) const
{
    for (ushint index = 0; index < word.size(); ++index)
    {
        if (!isPointerMathOperator(word[index]) && !isReferenceMathOperator(word[index]))
        {
            return false;
        }
    }
    return true;
}
bool NorminetteCorrector::isPointerMathOperator(const std::string& word) const
{
    for (ushint index = 0; index < word.size(); ++index)
    {
        if (word[index] != '*')
        {
            return false;
        }
    }
    return true;
}
bool NorminetteCorrector::isReferenceMathOperator(const std::string& word) const
{
    for (ushint index = 0; index < word.size(); ++index)
    {
        if (word[index] != '&')
        {
            return false;
        }
    }
    return true;
}
bool NorminetteCorrector::isPointerMathOperator(const char symbol) const
{
    return(symbol == '*');
}
bool NorminetteCorrector::isReferenceMathOperator(const char symbol) const
{
    return(symbol == '&');
}
bool NorminetteCorrector::isIncrementOrDecrement(const std::string& Symbol) const
{
    if (Symbol.empty() || Symbol.size() > 2)
    {
        return false;
    }
    
    if (Symbol.size() == 1)
    {
        const char symbol = Symbol.front();

        if (symbol == '+' || symbol == '-')
        {
            return (true);
        }
        return false;
    }
    else
    {
        if (Symbol == "++" || Symbol == "--")
        {
            return (true);
        }
        return false;
    }
}
void NorminetteCorrector::correctIncrementOrDecrement(ushint indexLine, ushint indexWord)
{
    std::vector<std::string> line = FileTextEditor::getLine(indexLine);

    if (std::isalpha(line[(int)indexWord + 1].front()) || std::isdigit(line[(int)indexWord + 1].front()))
    {
        FileTextEditor::combineWords(indexLine, indexWord, indexWord + 1);
    }
    else
    {
        FileTextEditor::combineWords(indexLine, indexWord - 1, indexWord);
    }
}
int  NorminetteCorrector::latestMathOperatorIndex(ushint indexLine, ushint indexWord)
{
    std::vector<std::string> line = FileTextEditor::getLine(indexLine);
    int indexEnd = indexWord;

    for (ushint start = indexWord + 1; start < line.size(); ++start)
    {
        if (!isMathOperator(line[start]))
        {
            break;
        }
        ++indexEnd;
    }
    return indexEnd;
}
int  NorminetteCorrector::latestMathOperatorIndex(std::vector<std::string>& line, ushint indexWord)
{
    int indexEnd = indexWord;

    for (ushint start = indexWord + 1; start < line.size(); ++start)
    {
        if (isMathOperator(line[start]))
        {
            ++indexEnd;
        }
    }
    return indexEnd;
}

void NorminetteCorrector::correctBrackets()
{
    correctRoundBrackets();
}
void NorminetteCorrector::correctRoundBrackets()
{
    for (ushint indexLine = 0; indexLine < FileTextEditor::size(); ++indexLine)
    {
        searchBracketsInLine(indexLine);
    }
}
void NorminetteCorrector::searchBracketsInLine(int indexLine)
{
    std::vector<std::string> words = FileTextEditor::getLine(indexLine);

    for (ushint indexWord = 0; indexWord < words.size(); ++indexWord)
    {
        if      (words[indexWord] == "(")
        {
            correctOpenRoundBrackets(indexLine, words, indexWord);
        }
        else if (words[indexWord] == ")")
        {
            correctCloseRoundBrackets(indexLine, words, indexWord);
        }
        else if (words[indexWord] == "[")
        {
            correctOpenSquareBrackets(indexLine, words, indexWord);
        }
        else if (words[indexWord] == "]")
        {
            correctCloseSquareBrackets(indexLine, words, indexWord);
        }
    }
}
void NorminetteCorrector::correctOpenRoundBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord)
{
    if (indexWord == 0)
    {
        FileTextEditor::combineWords(indexLine, indexWord, indexWord + 1);
        words = FileTextEditor::getLine(indexLine);
        return;
    }
        
    const std::vector<std::string> keyWords{ "if", "while", "return" };
    bool key = true;
    for (ushint indexKeyWord = 0; indexKeyWord < keyWords.size(); ++indexKeyWord)
    {
        if (keyWords[indexKeyWord] == words[indexWord - 1])
        {
            key = false;
        }
        else if (NorminetteCorrector::isMathOperator(words[indexWord - 1]))
        {
            key = false;
        }
    }
    if (key)
    {
        FileTextEditor::combineWords(indexLine, indexWord - 1, indexWord + 1);
        --indexWord;
        words = FileTextEditor::getLine(indexLine);
    }
    else
    {
        FileTextEditor::combineWords(indexLine, indexWord, indexWord + 1);
        words = FileTextEditor::getLine(indexLine);
    }
}
void NorminetteCorrector::correctCloseRoundBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord)
{
    FileTextEditor::combineWords(indexLine, indexWord - 1, indexWord);
    words = FileTextEditor::getLine(indexLine);
}
void NorminetteCorrector::correctOpenSquareBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord)
{
    if (indexWord == 0)
    {
        FileTextEditor::combineWords(indexLine, indexWord, indexWord + 1);
        words = FileTextEditor::getLine(indexLine);
        return;
    }

    FileTextEditor::combineWords(indexLine, indexWord - 1, indexWord + 1);
    words = FileTextEditor::getLine(indexLine);
    --indexWord;
}
void NorminetteCorrector::correctCloseSquareBrackets(ushint indexLine, std::vector<std::string>& words, ushint& indexWord)
{
    FileTextEditor::combineWords(indexLine, indexWord - 1, indexWord);
    words = FileTextEditor::getLine(indexLine);
}

void NorminetteCorrector::beforeSemicolonShouldBeNoSpace()
{
    for (ushint start = 0; start < FileTextEditor::size(); ++start)
    {
        std::vector<std::string> line = FileTextEditor::getLine(start);
        if (line.back() == ";")
        {
            FileTextEditor::combineWords(start, static_cast<ushint>(line.size() - 2), static_cast<ushint>(line.size() - 1));
        }
    }
}
void NorminetteCorrector::correctComma()
{
    for (ushint indexLine = 0; indexLine < FileTextEditor::size(); ++indexLine)
    {
        correctCommaInLine(indexLine);
    }
}
void NorminetteCorrector::correctCommaInLine(ushint indexLine)
{
    std::vector<std::string> line = FileTextEditor::getLine(indexLine);

    if (line.size() <= 4)
        return;

    for (ushint indexWord = 0; indexWord < line.size(); ++indexWord)
    {
        if (line[indexWord] == ",")
        {
            FileTextEditor::combineWords(indexLine, indexWord - 1, indexWord);
            line = FileTextEditor::getLine(indexLine);
        }
    }
}

void   NorminetteCorrector::correctTabulation()
{
    correctTabulationBeforeVariableNames();
    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        ushint startFunction = m_BracesIndex[start].front();
        ushint endFunction   = -m_BracesIndex[start].back();
        correctTabulationInFunction(startFunction + 1, endFunction - 1);
    }
}
void   NorminetteCorrector::correctTabulationInFunction(ushint indexStart, ushint indexEnd)
{
    for (ushint indexLine = indexStart; indexLine <= indexEnd; ++indexLine)
    {
        correctTabulationInLine(indexLine);
    }
}
void   NorminetteCorrector::correctTabulationInLine(ushint indexLine)
{
    std::string tabs = "";
    ushint count = NorminetteCorrector::getTabulationCount(indexLine);
    
    for (ushint indexCount = 0; indexCount < count; ++indexCount)
    {
        tabs += '\t';
    }

    if (indexLine > 0)
    {
        const std::string word = FileTextEditor::getLine(indexLine - 1).back();
        if ((word.back() == ')' || word == "else") && !isBracesIndex(indexLine))
        {
            tabs += '\t';
        }
    }

    FileTextEditor::addWordInLine(indexLine, 0, tabs);
}
ushint NorminetteCorrector::getTabulationCount(ushint indexLine)
{
    for (ushint indexFunction = 0; indexFunction < m_BracesIndex.size(); ++indexFunction)
    {
        if (indexLine > NorminetteCorrector::getPositive(m_BracesIndex[indexFunction].back()))
            continue;
        return (getTabulationCountInFunction(indexFunction, indexLine));
    }
    return 0;
}
ushint NorminetteCorrector::getTabulationCountInFunction(ushint indexFunction, ushint indexLine)
{
    int countOpenBraces = 0;
    int countCloseBraces = 0;

    for (ushint index = 0; index < m_BracesIndex[indexFunction].size(); ++index)
    {
        if (indexLine < NorminetteCorrector::getPositive(m_BracesIndex[indexFunction][index]))
        {
            return (countOpenBraces + countCloseBraces);
        }
        if (indexLine == NorminetteCorrector::getPositive(m_BracesIndex[indexFunction][index]))
        {
            if(m_BracesIndex[indexFunction][index] > 0)
                return (countOpenBraces + countCloseBraces);
            else
                return (countOpenBraces + countCloseBraces - 1);
        }
        if (m_BracesIndex[indexFunction][index] > 0)
            ++countOpenBraces;
        if (m_BracesIndex[indexFunction][index] < 0)
            --countCloseBraces;
    }
    return (countOpenBraces + countCloseBraces + 1);
}
bool NorminetteCorrector::isBracesIndex(const ushint indexLine) const 
{
    for (ushint start = 0; start < m_BracesIndex.size(); ++start)
    {
        if (indexLine > NorminetteCorrector::getPositive(m_BracesIndex[start].back()))
        {
            continue;
        }
        for (ushint index = 0; index < m_BracesIndex[start].size(); ++index)
        {
            if (indexLine == NorminetteCorrector::getPositive(m_BracesIndex[start][index]))
            {
                return true;
            }
        }
    }
    return false;
}

void NorminetteCorrector::correctTabulationBeforeVariableNames()
{

    std::vector<ushint> indexDeclarationLine;
    searchFunctionNames(indexDeclarationLine);
    searchDeclarationVaribaleNames(indexDeclarationLine);

    std::vector<ushint> indexKeyWord = getIndexKeyWordsOfTabulationForVaribaleAndFunctionNames(indexDeclarationLine);
    std::vector<ushint> sizeKeyWords = getSizeKeyWordsOfTabulationForVaribaleAndFunctionNames(indexDeclarationLine, indexKeyWord);
    correctTabulationForVaribaleAndFunctionNames(indexDeclarationLine, indexKeyWord, sizeKeyWords);
}
void NorminetteCorrector::searchFunctionNames(std::vector<ushint>& indexDeclarationLine)
{
    indexDeclarationLine.resize(m_BracesIndex.size());

    for (ushint index = 0; index < m_BracesIndex.size(); ++index)
    {
        indexDeclarationLine[index] = m_BracesIndex[index].front() - 1;
    }
}
void NorminetteCorrector::searchDeclarationVaribaleNames(std::vector<ushint>& indexDeclarationLine)
{
    for (ushint indexFunction = 0; indexFunction < m_BracesIndex.size(); ++indexFunction)
    {
        searchDeclarationVaribaleNamesInFuntion(indexDeclarationLine, indexFunction);
    }
}
void NorminetteCorrector::searchDeclarationVaribaleNamesInFuntion(std::vector<ushint>& indexDeclarationLine, ushint indexFunction)
{
    for (ushint indexLine = m_BracesIndex[indexFunction].front() + 1; indexLine < -m_BracesIndex[indexFunction].back(); ++indexLine)
    {
        if (!isThereDeclarationInLine(indexLine))
        {
            return ;
        }
        indexDeclarationLine.push_back(indexLine);
    }
}
std::vector<ushint> NorminetteCorrector::getIndexKeyWordsOfTabulationForVaribaleAndFunctionNames(const std::vector<ushint>& indexDeclarationLine)
{
    std::vector<ushint> indexDeclarationOfLines(indexDeclarationLine.size());

    for (ushint index = 0; index < indexDeclarationLine.size(); ++index)
    {
        std::vector<std::string>& line = FileTextEditor::getLine(indexDeclarationLine[index]);
        indexDeclarationOfLines[index] = getDeclarationKeyWordIndexInLine(line);
    }

    return indexDeclarationOfLines;
}
std::vector<ushint> NorminetteCorrector::getSizeKeyWordsOfTabulationForVaribaleAndFunctionNames(const std::vector<ushint>& indexDeclarationLine, const std::vector<ushint>& indexKeyWord)
{
    std::vector<ushint> sizeDeclarationOfLines(indexDeclarationLine.size());

    for (ushint index = 0; index < indexDeclarationLine.size(); ++index)
    {
        std::vector<std::string>& line = FileTextEditor::getLine(indexDeclarationLine[index]);
        sizeDeclarationOfLines[index] = getDeclarationSizeInLine(line, indexKeyWord[index]);
    }

    return sizeDeclarationOfLines;
}
shint NorminetteCorrector::getDeclarationSizeInFunction(ushint indexLine)
{
    std::vector<std::string>& line = FileTextEditor::getLine(indexLine);

    shint indexWord = getDeclarationKeyWordIndexInLine(line);

    return getDeclarationSizeInLine(line, indexWord);
}
shint NorminetteCorrector::getDeclarationKeyWordIndexInLine(const std::vector<std::string>& line)
{
    ushint index = 0;
    bool key = true;
    for (; index < line.size(); ++index)
    {
        if (key && isWordDeclarationKeyWord(line[index]))
        {
            key = false;
            continue;
        }
        if (!key && !isWordDeclarationKeyWord(line[index]))
        {
            break;
        }
    }
    return index;
}
shint NorminetteCorrector::getDeclarationSizeInLine(const std::vector<std::string>& line, ushint indexWord)
{
    shint size = 0; 

    if (indexWord < 0)
        return 0;

    for (ushint index = 0; index < indexWord; ++index)
    {
        size += static_cast<ushint>(line[index].size());
    }
    if (indexWord != 0)
        size += indexWord - 1;

    return size;
}
void NorminetteCorrector::correctTabulationForVaribaleAndFunctionNames(const std::vector<ushint>& indexDeclarationLine, const std::vector<ushint>& indexKeyWord, std::vector<ushint> sizeKeyWord)
{
    constexpr ushint tabSize = 8;
    //shint maxValue = getMaxDeclarationSize(sizeKeyWord);
    //maxValue = (maxValue / tabSize + 1) * tabSize;
    shint maxValue = (getMaxDeclarationSize(sizeKeyWord) / tabSize + 1) * tabSize;

    for (ushint index = 0; index < indexDeclarationLine.size(); ++index)
    {
        //NAYEL
        //std::vector<std::string>& line = FileTextEditor::getLine(indexDeclarationLine[index]);
        ushint lineKeyWordSize = sizeKeyWord[index];
        lineKeyWordSize = maxValue - lineKeyWordSize;

        shint count = (lineKeyWordSize % tabSize) == 0 ? (lineKeyWordSize / tabSize) : (lineKeyWordSize / tabSize + 1);
        std::string newWord = initTabCountWord(count);
        if (isDeclarationInFunction(NorminetteCorrector::getFunctionStart(indexDeclarationLine[index])) - 1)
            if (isDeclarationLineFunctionName(indexDeclarationLine[index]))
                newWord += '\t';


        FileTextEditor::addWordInLine(indexDeclarationLine[index], indexKeyWord[index], newWord);
    }
}
bool  NorminetteCorrector::isDeclarationInFunction(int indexFunction)
{
    return (NorminetteCorrector::isThereDeclarationInLine(indexFunction + 1));
}
shint NorminetteCorrector::getMaxDeclarationSize(const std::vector<ushint>& sizeKeyWord)
{
    if (sizeKeyWord.empty())
        return -1;
    shint maxValue = sizeKeyWord[0];
    for (ushint index = 1; index < sizeKeyWord.size(); ++index)
    {
        if (sizeKeyWord[index] > maxValue)
        {
            maxValue = sizeKeyWord[index];
        }
    }
    return maxValue;
}
std::string NorminetteCorrector::initTabCountWord(int count)
{
    std::string newWord = "";
    
    for (ushint index = 0; index < count; ++index)
    {
        newWord += '\t';
    }
    return newWord;
}
bool NorminetteCorrector::isDeclarationLineFunctionName(ushint indexLine)
{
    std::vector<std::string>& line = FileTextEditor::getLine(indexLine);

    if (line.size() > 1)
    {
        return (line.back().back() == ')');;
    }
    else if (line.back().size() == 1)
    {
        return (line.back() == ")");
    }
    return false;
}

void NorminetteCorrector::addFewerLines()
{
    addFewerLinesToFunctions();
    addFewerLinesToDeclaration();
}
void NorminetteCorrector::addFewerLinesToFunctions()
{
    const std::string newEmptyLine = "";

    for (ushint index = 0; index < m_BracesIndex.size() - 1; ++index)
    {
        NorminetteCorrector::addNewLine(-m_BracesIndex[index].back() + 1, newEmptyLine);
    }
}
void NorminetteCorrector::addFewerLinesToDeclaration()
{
    const std::string newEmptyLine = "";

    for (ushint index = 0; index < m_BracesIndex.size(); ++index)
    {
        ushint indexDeclaration = NorminetteCorrector::searchDeclarationStartInFunction(m_BracesIndex[index].front(), -m_BracesIndex[index].back());
        if(FileTextEditor::getLine(indexDeclaration - 1).front() != "{")
            NorminetteCorrector::addNewLine(indexDeclaration, newEmptyLine);
    }

}