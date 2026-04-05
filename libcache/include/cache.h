#ifndef CACHE_H
#define CACHE_H

typedef struct cache cache_t;

cache_t* cache_create(int capacity);
void cache_put(cache_t *c, const char *key, const char *value);
const char* cache_get(cache_t *c, const char *key);
void cache_free(cache_t *c);

#endif
