#ifndef RE_MEMORY_UTILS_H
#define RE_MEMORY_UTILS_H

#define RE_GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define RE_GROW_ARRAY(array_type, array, old_capacity, new_capacity) (array_type*)RE_Reallocate(array, sizeof(array_type) * (old_capacity), sizeof(array_type) * (new_capacity))
#define RE_FREE_ARRAY(array_type, array, capacity) RE_Reallocate(array, sizeof(array_type) * capacity, 0)

void* RE_Reallocate(void* pointer, size_t old_capacity, size_t new_capacity);

#endif // RE_MEMORY_UTILS_H