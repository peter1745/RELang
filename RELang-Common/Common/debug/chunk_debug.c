#include "chunk_debug.h"
#include "Common/bytecode/value.h"

void RE_DisassembleChunk(const RE_Chunk* chunk, const char* debugName)
{
    printf("---------- Disassemble '%s' ----------\n", debugName);

    for (u32 offset = 0; offset < chunk->count; )
        offset = RE_DisassembleInstruction(chunk, offset);
    
}

static u32 RE_SimpleInstruction(const char* name, u32 offset)
{
    printf("%s\n", name);
    return offset + 1;
}

static u32 RE_ConstantInstruction(const char* name, const RE_Chunk* chunk, u32 offset)
{
    // The index to the constant should be located immediately after our OP code
    byte constant_index = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant_index);
    RE_PrintValue(chunk->constants.values[constant_index]);
    printf("'\n");
    return offset + 2;
}

u32 RE_DisassembleInstruction(const RE_Chunk* chunk, u32 offset)
{
    printf("%04d", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    {
        printf("   | ");
    }
    else
    {
        printf("%4d ", chunk->lines[offset]);
    }

    u32 instruction = chunk->code[offset];
    switch (instruction)
    {
    case RE_OP_CONSTANT:
        return RE_ConstantInstruction("RE_OP_CONSTANT", chunk, offset);
    case RE_OP_ADD:
        return RE_SimpleInstruction("RE_OP_ADD", offset);
    case RE_OP_SUBTRACT:
        return RE_SimpleInstruction("RE_OP_SUBTRACT", offset);
    case RE_OP_MULTIPLY:
        return RE_SimpleInstruction("RE_OP_MULTIPLY", offset);
    case RE_OP_DIVIDE:
        return RE_SimpleInstruction("RE_OP_DIVIDE", offset);
    case RE_OP_NEGATE:
        return RE_SimpleInstruction("RE_OP_NEGATE", offset);
    case RE_OP_RETURN:
        return RE_SimpleInstruction("RE_OP_RETURN", offset);
    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}
