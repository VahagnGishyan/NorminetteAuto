#include "..\Header.h"
#include "..\FileEditor\FileEditor.h"
#include "..\FileTextEditor\FileTextEditor.h"
#include "NorminetteCorrector.h"

int main()
{
    NorminetteCorrector data("data.txt");
    data.correctAll();

    return (0);
}