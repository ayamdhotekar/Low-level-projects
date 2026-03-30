#ifndef THREADPOOL_H
#define THREADPOOL_H

typedef struct threadpool threadpool_t;

threadpool_t* threadpool_create(int num_threads);
void threadpool_add(threadpool_t *pool, void (*function)(void*), void *arg);
void threadpool_destroy(threadpool_t *pool);

#endif
