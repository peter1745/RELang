#include <stdlib.h>

#include "memory_utils.h"

void* RE_Reallocate(void* pointer, size_t old_capacity, size_t new_capacity)
{
    if (new_capacity == 0)
    {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, new_capacity);

    if (result == NULL)
        exit(EXIT_FAILURE);
    
    return result;
}
