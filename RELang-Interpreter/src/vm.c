#include "vm.h"
#include "Common/debug/chunk_debug.h"

#define RE_DEBUG_TRACE_EXECUTION 1

RE_VM vm;

static void RE_ResetStack()
{
    vm.stackTop = vm.stack;
}

void RE_InitVM()
{
    RE_ResetStack();
}

static byte RE_ReadNextByte()
{
    byte result = *vm.ip;
    vm.ip++;
    return result;
}

static RE_InterpretResult RE_RunVM()
{
#define RE_BINARY_OP(op) \
    do { \
        RE_Value b = RE_StackPop(); \
        RE_Value a = RE_StackPop(); \
        RE_StackPush(a op b); \
    } while (false)

    for (;;)
    {
#if RE_DEBUG_TRACE_EXECUTION
        printf("         ");
        for (RE_Value* slot = vm.stack; slot < vm.stackTop; slot++)
        {
            printf("[ ");
            RE_PrintValue(*slot);
            printf(" ]");
        }
        printf("\n");

        RE_DisassembleInstruction(vm.chunk, (u32)(vm.ip - vm.chunk->code));
#endif

        byte instruction;
        switch (instruction = RE_ReadNextByte())
        {
        case RE_OP_CONSTANT:
        {
            RE_Value constant = vm.chunk->constants.values[RE_ReadNextByte()];
            RE_StackPush(constant);
            break;
        }
        case RE_OP_ADD:
        {
            RE_BINARY_OP(+);
            break;
        }
        case RE_OP_SUBTRACT:
        {
            RE_BINARY_OP(-);
            break;
        }
        case RE_OP_MULTIPLY:
        {
            RE_BINARY_OP(*);
            break;
        }
        case RE_OP_DIVIDE:
        {
            RE_BINARY_OP(/);
            break;
        }
        case RE_OP_NEGATE:
        {
            RE_StackPush(-RE_StackPop());
            break;
        }
        case RE_OP_RETURN:
        {
            RE_PrintValue(RE_StackPop());
            printf("\n");
            return RE_INTERPRET_OK;
        }
        }
    }

#undef RE_BINARY_OP
}

RE_InterpretResult RE_VMInterpret(RE_Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return RE_RunVM();
}

void RE_StackPush(RE_Value value)
{
    *vm.stackTop = value;
    vm.stackTop++;
}

RE_Value RE_StackPop()
{
    vm.stackTop--;
    return *vm.stackTop;
}

void RE_FreeVM()
{

}

