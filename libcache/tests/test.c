#include <stdio.h>
#include "../include/cache.h"

int main() {
    cache_t *c = cache_create(2);

    cache_put(c, "a", "1");
    cache_put(c, "b", "2");

    printf("a: %s\n", cache_get(c, "a"));

    cache_put(c, "c", "3");

    printf("b: %s\n", cache_get(c, "b"));
    printf("c: %s\n", cache_get(c, "c"));

    cache_free(c);
    return 0;
}
