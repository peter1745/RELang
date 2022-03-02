#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Common/utils/file_utils.h"

#include "vm.h"

RE_InterpretResult RE_InterpretByteCode(byte* byte_code)
{

}

void RE_RunFile(const char* file_path)
{
    byte* byte_code = RE_ReadFile(file_path);

    if (byte_code == NULL)
    {
        printf("Failed to read byte code from %s", file_path);
        return;
    }

    RE_InterpretResult result = RE_InterpretByteCode(byte_code);
    free(byte_code);

    if (result == RE_INTERPRET_COMPILE_ERROR) exit(64);
    if (result == RE_INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: RERun.sh file");
        return EXIT_FAILURE;
    }

    RE_InitVM();
    RE_RunFile(argv[1]);
    RE_FreeVM();
    return EXIT_SUCCESS;
}