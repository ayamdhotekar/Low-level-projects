#include <stdlib.h>
#include "../include/ds.h"

#define INITIAL_CAP 4

Vector* vector_create() {
    Vector *v = malloc(sizeof(Vector));
    v->size = 0;
    v->capacity = INITIAL_CAP;
    v->data = malloc(sizeof(void*) * v->capacity);
    return v;
}

void vector_push(Vector *v, void *item) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(void*) * v->capacity);
    }
    v->data[v->size++] = item;
}

void* vector_get(Vector *v, size_t index) {
    if (index >= v->size) return NULL;
    return v->data[index];
}

void vector_free(Vector *v) {
    free(v->data);
    free(v);
}

Stack* stack_create() {
    Stack *s = malloc(sizeof(Stack));
    s->vec = vector_create();
    return s;
}

void stack_push(Stack *s, void *item) {
    vector_push(s->vec, item);
}

void* stack_pop(Stack *s) {
    if (s->vec->size == 0) return NULL;
    return s->vec->data[--s->vec->size];
}

void stack_free(Stack *s) {
    vector_free(s->vec);
    free(s);
}
