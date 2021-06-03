#include "NorminetteAuto.h"

int main(int argc, char** argv)
{
    for(ushint index = 1; index < argc; ++index)
    {
        NorminetteAuto::CorrectFile(argv[index]);
    }

    return (0);
}