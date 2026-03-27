#ifndef DS_H
#define DS_H

#include <stddef.h>

// Vector
typedef struct {
    void **data;
    size_t size;
    size_t capacity;
} Vector;

Vector* vector_create();
void vector_push(Vector *v, void *item);
void* vector_get(Vector *v, size_t index);
void vector_free(Vector *v);

// Stack
typedef struct {
    Vector *vec;
} Stack;

Stack* stack_create();
void stack_push(Stack *s, void *item);
void* stack_pop(Stack *s);
void stack_free(Stack *s);

#endif
