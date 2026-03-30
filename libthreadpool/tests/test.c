#include <stdio.h>
#include <unistd.h>
#include "../include/threadpool.h"

void task(void *arg) {
    int num = *(int*)arg;
    printf("Processing %d\n", num);
    sleep(1);
}

int main() {
    threadpool_t *pool = threadpool_create(4);

    int nums[8];
    for (int i = 0; i < 8; i++) {
        nums[i] = i;
        threadpool_add(pool, task, &nums[i]);
    }

    sleep(3);
    threadpool_destroy(pool);
    return 0;
}
