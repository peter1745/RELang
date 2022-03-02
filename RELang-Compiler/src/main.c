#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 3 || strcmp(argv[1], "--compile") != 0)
    {
        printf("Usage: relang --compile [file/path]");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}