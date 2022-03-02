#include "compiler.h"
#include "scanner.h"

void RE_CompileFromSource(const char* source)
{
    RE_InitScanner(source);
}
