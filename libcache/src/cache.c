#include <stdlib.h>
#include <string.h>
#include "../include/cache.h"

typedef struct node {
    char *key;
    char *value;
    struct node *prev, *next;
} node_t;

struct cache {
    int capacity;
    int size;
    node_t *head;
};

static node_t* create_node(const char *k, const char *v) {
    node_t *n = malloc(sizeof(node_t));
    n->key = strdup(k);
    n->value = strdup(v);
    n->prev = n->next = NULL;
    return n;
}

cache_t* cache_create(int capacity) {
    cache_t *c = malloc(sizeof(cache_t));
    c->capacity = capacity;
    c->size = 0;
    c->head = NULL;
    return c;
}

static void remove_tail(cache_t *c) {
    if (!c->head) return;
    node_t *curr = c->head;
    while (curr->next) curr = curr->next;

    if (curr->prev) curr->prev->next = NULL;
    else c->head = NULL;

    free(curr->key);
    free(curr->value);
    free(curr);
    c->size--;
}

void cache_put(cache_t *c, const char *key, const char *value) {
    node_t *curr = c->head;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            free(curr->value);
            curr->value = strdup(value);
            return;
        }
        curr = curr->next;
    }

    node_t *n = create_node(key, value);
    n->next = c->head;
    if (c->head) c->head->prev = n;
    c->head = n;
    c->size++;

    if (c->size > c->capacity)
        remove_tail(c);
}

const char* cache_get(cache_t *c, const char *key) {
    node_t *curr = c->head;

    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return curr->value;
        curr = curr->next;
    }
    return NULL;
}

void cache_free(cache_t *c) {
    node_t *curr = c->head;
    while (curr) {
        node_t *next = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        curr = next;
    }
    free(c);
}
