#include "NorminetteCorrector.h"

//for work
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

    std::string reservData = getLineIndex(argIndex);
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

    print();
    preliminaryCorrectingFileFormat();
    print();

    correctInsideLine();
    print();
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
        if (getLineIndex(start)[0] != '#')
        {
            break;
        }
    }
    if (getLineIndex(start).size() != 0)
        addNewLineIndex(start, "");
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
        std::string line = getLineIndex(start);

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
        std::string line = getLineIndex(start);
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
    std::vector< std::vector<std::string>> text;

    for (ushint start = m_startLine; start < size(); ++start)
    {
        std::vector<std::string> line = separateByKeySymbols(start);
        text.push_back(line);
    }
    //skzbunq, 
    //Stroev grnac metodnery chpetq a poxen m_data-n u bun texty 
    //menak karan poxen line-ery, 
    //line-ery popoxelov berum enq verjnakan tesqi
    //vorn el verjum  poxum a m_data-yi parunakutyuny.

    for(ushint indexLine = 0; indexLine < text.size();++indexLine)
    {
        correctSemicolon(indexLine, text);
    }

    for (ushint indexLine = 0; indexLine < text.size(); ++indexLine)
    {
        correctIfWhile(indexLine, text);
    }

    for (ushint indexLine = 0; indexLine < text.size(); ++indexLine)
    {
        correctReturns(indexLine,text);
    }

    for (ushint indexLine = 0; indexLine < text.size(); ++indexLine)
    {
        std::vector<std::string>& line = text[indexLine];

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

    for (ushint start = size() - 1; start >= text.size() + m_startLine; --start)
        FileEditor::deleteLineBack();
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
void NorminetteCorrector::addNewLineInTextIndex(const unsigned short indexLine, std::vector< std::vector<std::string>>& text, const std::vector<std::string>& newLine)
{
    std::vector<std::string> Line = newLine;
    ushint size = static_cast<ushint>(text.size());

    for (unsigned short int index = indexLine; index < size; ++index)
    {
        std::vector<std::string> registerLine = text[index];
        text[index] = Line;
        Line = registerLine;
    }
    text.push_back(Line);
}
void NorminetteCorrector::deleteLineInTextIndex(const unsigned short indexLine, std::vector< std::vector<std::string>>& text)
{
    for (unsigned short int index = indexLine; index < size() - 1; ++index)
    {
        text[index] = text[index + 1];
    }
    text.pop_back();
}

void NorminetteCorrector::correctSemicolon(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{
    if (text[indexLine].size() == 1 && text[indexLine][0] == ";")
    {
        aloneSemicolonRaiseUp(indexLine, text);
    }
    deleteUnnecessarySemicolon(indexLine, text);
    //beforeSemicolonShouldBeNoSpace(indexLine, text);
    
}
void NorminetteCorrector::aloneSemicolonRaiseUp(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{
    if (indexLine == 9)
        std::cout;
    text[indexLine - 1].back() = text[indexLine - 1].back() + ";";
    
    for (ushint start = indexLine; start < text.size() - 1; ++start)
    {
        text[start] = text[start + 1];
    }
    text.pop_back();

    --indexLine;
}
void NorminetteCorrector::deleteUnnecessarySemicolon(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{
    std::string line = text[indexLine].back();

    if (line.empty() || line.size() == 1 || line.back() != ';')
        return;
    for (shint index = line.size() - 2; index >= 0; --index)
    {
        if (line[index] == ';')
            line.pop_back();
    }

    text[indexLine].back() = line;
}
void NorminetteCorrector::beforeSemicolonShouldBeNoSpace(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{
    std::vector <std::string> line = text[indexLine];

    int indexLineEnd = static_cast<int>(line.size()) - 1;

    if (indexLineEnd == 0 || line[indexLineEnd] != ";")
        return;

    line[indexLineEnd - 1] += line[indexLineEnd];
    line.pop_back();
    text[indexLine] = line;

}

void NorminetteCorrector::correctIfWhile(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{


    correctIf(indexLine, text);
    correctWhile(indexLine, text);



}
void NorminetteCorrector::correctIf(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{
    //after if should be no space

    std::vector<std::string>& line = text[indexLine];
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

    for (ushint index = line.size() - 1; index > start; --index)
    {
        line.pop_back();
    }

    addNewLineInTextIndex(indexLine + 1, text, newData);

    //std::vector<std::string> forNotError;
    //forNotError[0] = "{";
    ////addNewLineInTextIndex(indexLine + 1, text, "{");
    //addNewLineInTextIndex(indexLine + 1, text, forNotError);
    //addNewLineInTextIndex(indexLine + 2, text, newData);
    ////addNewLineInTextIndex(indexLine + 3, text, "}");
    //forNotError[0] = "}";
    //addNewLineInTextIndex(indexLine + 3, text, forNotError);
}
void NorminetteCorrector::correctWhile(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{
    //after while should be no space

    std::vector<std::string>& line = text[indexLine];
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

    for (ushint index = line.size() - 1; index > start; --index)
    {
        line.pop_back();
    }

    addNewLineInTextIndex(indexLine + 1, text, newData);
}

void NorminetteCorrector::correctReturns(ushint& indexLine, std::vector< std::vector<std::string>>& text)
{
    std::vector<std::string> line = text[indexLine];
    const std::string keyWord = "return";

    if (line.size() < 2 || !searchInWords(line, keyWord))
        return;

    //for testing, not for relise
    assert(line.front() == keyWord && "Whil be a return");

    if (line[1] == "(")
        return;

    std::vector<std::string> data;

    data.push_back(line.front());
    data.push_back("(");

    for (ushint index = 2; index < line.size() - 1; ++index)
    {
        data.push_back(line[index]);
    }

    data.push_back(")");
    data.push_back(line.back());
}
