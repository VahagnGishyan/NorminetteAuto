#include "NorminetteAuto.h"
#include <iostream>
   
int main(int argc, char**argv) 
{
    for(ushint index = 1; index <= argc; ++index)
    {
        NorminetteAuto::CorrectFile("../Data/ft_atoi.c");
    }
    
    //NorminetteAuto::CorrectFilesInFile(argv[index]);
    //NorminetteAuto::CorrectFile("../Data/Libft.c");

    //std::ofstream file("newFile.c");
    //file.write("#include <iostream>\0", 20);
    //
    //file.close();

    //std::ifstream newFile("newFile.c");
    //char arr[20];
    //newFile.read(arr, 20);
    //std::string a(arr);
    //std::cout << arr << std::endl;

    return (0);
}


