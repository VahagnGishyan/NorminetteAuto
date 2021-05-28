#include "..\Header.h"
#include "..\FileEditor\FileEditor.h"
#include "..\FileTextEditor\FileTextEditor.h"
#include "..\NorminetteCorrector\NorminetteCorrector.h"

int main()
{
    NorminetteCorrector data("..\\Data\\data.txt");
    data.correctAll();

    return (0);
}