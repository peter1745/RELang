#ifndef RE_CHUNK_H
#define RE_CHUNK_H

#include "value.h"

typedef enum {
    RE_OP_CONSTANT,
    RE_OP_ADD,
    RE_OP_SUBTRACT,
    RE_OP_MULTIPLY,
    RE_OP_DIVIDE,
    RE_OP_NEGATE,
    RE_OP_RETURN
} RE_OpCode;

typedef struct {
    u32 count;
    u32 capacity;
    byte* code;
    u16* lines;
    RE_ValueArray constants;
} RE_Chunk;

void RE_InitChunk(RE_Chunk* chunk);
void RE_ChunkWrite(RE_Chunk* chunk, byte value, u16 line);
u32 RE_ChunkAddConstant(RE_Chunk* chunk, RE_Value value);
void RE_FreeChunk(RE_Chunk* chunk);

#endif