#ifndef RE_VM_H
#define RE_VM_H

#include "Common/bytecode/chunk.h"

#define RE_STACK_MAX 256

typedef struct {
    RE_Chunk* chunk;
    byte* ip;
    RE_Value stack[RE_STACK_MAX];
    RE_Value* stackTop;
} RE_VM;

typedef enum {
    RE_INTERPRET_OK,
    RE_INTERPRET_COMPILE_ERROR,
    RE_INTERPRET_RUNTIME_ERROR
} RE_InterpretResult;

void RE_InitVM();
RE_InterpretResult RE_VMInterpret(RE_Chunk* chunk);
void RE_StackPush(RE_Value value);
RE_Value RE_StackPop();
void RE_FreeVM();

#endif // RE_VM_H