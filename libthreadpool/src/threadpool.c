#include <pthread.h>
#include <stdlib.h>
#include "../include/threadpool.h"

typedef struct task {
    void (*function)(void*);
    void *arg;
    struct task *next;
} task_t;

struct threadpool {
    pthread_t *threads;
    task_t *task_queue;
    pthread_mutex_t lock;
    pthread_cond_t notify;
    int thread_count;
    int stop;
};

void* worker(void *arg) {
    threadpool_t *pool = (threadpool_t*)arg;

    while (1) {
        pthread_mutex_lock(&pool->lock);

        while (!pool->task_queue && !pool->stop) {
            pthread_cond_wait(&pool->notify, &pool->lock);
        }

        if (pool->stop) {
            pthread_mutex_unlock(&pool->lock);
            break;
        }

        task_t *task = pool->task_queue;
        pool->task_queue = task->next;

        pthread_mutex_unlock(&pool->lock);

        task->function(task->arg);
        free(task);
    }

    return NULL;
}

threadpool_t* threadpool_create(int num_threads) {
    threadpool_t *pool = malloc(sizeof(threadpool_t));
    pool->thread_count = num_threads;
    pool->task_queue = NULL;
    pool->stop = 0;

    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->notify, NULL);

    pool->threads = malloc(sizeof(pthread_t) * num_threads);

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&pool->threads[i], NULL, worker, pool);
    }

    return pool;
}

void threadpool_add(threadpool_t *pool, void (*function)(void*), void *arg) {
    task_t *task = malloc(sizeof(task_t));
    task->function = function;
    task->arg = arg;
    task->next = NULL;

    pthread_mutex_lock(&pool->lock);

    task_t *temp = pool->task_queue;
    if (!temp) {
        pool->task_queue = task;
    } else {
        while (temp->next) temp = temp->next;
        temp->next = task;
    }

    pthread_cond_signal(&pool->notify);
    pthread_mutex_unlock(&pool->lock);
}

void threadpool_destroy(threadpool_t *pool) {
    pthread_mutex_lock(&pool->lock);
    pool->stop = 1;
    pthread_cond_broadcast(&pool->notify);
    pthread_mutex_unlock(&pool->lock);

    for (int i = 0; i < pool->thread_count; i++) {
        pthread_join(pool->threads[i], NULL);
    }

    free(pool->threads);
    free(pool);
}
