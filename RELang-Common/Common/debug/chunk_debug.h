#ifndef RE_CHUNK_DEBUG_H
#define RE_CHUNK_DEBUG_H

#include "Common/bytecode/chunk.h"

void RE_DisassembleChunk(const RE_Chunk* chunk, const char* debugName);
u32 RE_DisassembleInstruction(const RE_Chunk* chunk, u32 offset);

#endif // RE_CHUNK_DEBUG_H