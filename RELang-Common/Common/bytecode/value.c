#include "value.h"

void RE_PrintValue(RE_Value value)
{
    printf("%g", value);
}

void RE_InitValueArray(RE_ValueArray* value_array)
{
    value_array->count = 0;
    value_array->capacity = 0;
    value_array->values = NULL;
}

void RE_ValueArrayWrite(RE_ValueArray* value_array, RE_Value value)
{
    if (value_array->capacity < value_array->count + 1)
    {
        u32 old_capacity = value_array->capacity;
        value_array->capacity = RE_GROW_CAPACITY(old_capacity);
        value_array->values = RE_GROW_ARRAY(RE_Value, value_array->values, old_capacity, value_array->capacity);
    }

    value_array->values[value_array->count] = value;
    value_array->count++;
}

void RE_FreeValueArray(RE_ValueArray* value_array)
{
    RE_FREE_ARRAY(RE_Value, value_array->values, value_array->capacity);
    RE_InitValueArray(value_array);
}

