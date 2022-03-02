#include "chunk.h"

void RE_InitChunk(RE_Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;

    RE_InitValueArray(&chunk->constants);
}

void RE_ChunkWrite(RE_Chunk* chunk, byte value, u16 line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        u32 old_capacity = chunk->capacity;
        chunk->capacity = RE_GROW_CAPACITY(old_capacity);
        chunk->code = RE_GROW_ARRAY(byte, chunk->code, old_capacity, chunk->capacity);
        chunk->lines = RE_GROW_ARRAY(u16, chunk->lines, old_capacity, chunk->capacity);
    }

    chunk->code[chunk->count] = value;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

u32 RE_ChunkAddConstant(RE_Chunk* chunk, RE_Value value)
{
    RE_ValueArrayWrite(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void RE_FreeChunk(RE_Chunk* chunk)
{
    RE_FREE_ARRAY(byte, chunk->code, chunk->capacity);
    RE_FREE_ARRAY(u16, chunk->lines, chunk->capacity);
    RE_FreeValueArray(&chunk->constants);
    RE_InitChunk(chunk);
}
