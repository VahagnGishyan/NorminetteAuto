#include "..\Header.h"
#include "..\FileEditor\FileEditor.h"
#include "..\FileTextEditor\FileTextEditor.h"

int main()
{
    FileTextEditor data("data.txt");
    data.print();

    return (0);
}