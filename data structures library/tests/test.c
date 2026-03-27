#include <stdio.h>
#include "../include/ds.h"

int main() {
    Stack *s = stack_create();

    int a = 10, b = 20, c = 30;

    stack_push(s, &a);
    stack_push(s, &b);
    stack_push(s, &c);

    printf("%d\n", *(int*)stack_pop(s));
    printf("%d\n", *(int*)stack_pop(s));

    stack_free(s);
    return 0;
}
