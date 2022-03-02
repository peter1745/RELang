#ifndef RE_VALUE_H
#define RE_VALUE_H

#include "Common/common.h"

typedef double RE_Value;

typedef struct {
    u32 count;
    u32 capacity;
    RE_Value* values;
} RE_ValueArray;

void RE_PrintValue(RE_Value value);

void RE_InitValueArray(RE_ValueArray* value_array);
void RE_ValueArrayWrite(RE_ValueArray* value_array, RE_Value value);
void RE_FreeValueArray(RE_ValueArray* value_array);

#endif // RE_VALUE_H