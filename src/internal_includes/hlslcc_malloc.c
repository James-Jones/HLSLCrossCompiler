#include <malloc.h>

void* (*hlslcc_malloc)(size_t size) = malloc;
void (*hlslcc_free)(void *p) = free;
void* (*hlslcc_realloc)(void *p,size_t size) = realloc;