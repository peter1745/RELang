#include "file_utils.h"

// TODO(Peter): Better error handling
byte* RE_ReadFile(const char* file_path)
{
    FILE* file = fopen(file_path, "r");

    if (file == NULL)
    {
        printf("Failed to open file '%s'\n", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    byte* buffer = (byte*)malloc(size + 1);
    if (buffer == NULL)
    {
        printf("Failed to allocate %d bytes!\n", size);
        fclose(file);
        return NULL;
    }

    size_t readSize = fread(buffer, sizeof(byte), size, file);

    if (readSize != size)
    {
        printf("Couldn't read entire file! Read %d bytes out of %d\n", readSize, size);
        fclose(file);
        return NULL;
    }

    // NOTE(Peter): Ensure that we always have a null-termination character
    buffer[readSize] = '\0';

    fclose(file);
    return buffer;
}
