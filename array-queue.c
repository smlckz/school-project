/* queue implemented using static array */

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_IMPLEMENTATION

#include "queue.h"

#define QUEUE_MAX PROJ_ARRAY_MAX

struct queue {
    size_t start, count;
    queue_elem array[QUEUE_MAX];
};

struct queue *queue_new(void)
{
    struct queue *queue = malloc(sizeof(struct queue));
    queue->start = 0;
    queue->count = 0;
    return queue;
}

void queue_free(struct queue *queue)
{
    free(queue);
}

enum queue_error enqueue(struct queue *queue, queue_elem elem)
{
    size_t cur;
    if (queue->count >= QUEUE_MAX)
        return QUEUE_ERR_FULL;
    cur = queue->start + queue->count++;
    if (cur >= QUEUE_MAX)
        cur %= QUEUE_MAX;
    queue->array[cur] = elem;
    return QUEUE_ERR_NONE;
}

enum queue_error dequeue(struct queue *queue, queue_elem *elem)
{
    if (queue->count == 0)
        return QUEUE_ERR_EMPTY;
    *elem = queue->array[queue->start++];
    queue->count--;
    if (queue->start >= QUEUE_MAX) {
        queue->start = 0;
    }
    return QUEUE_ERR_NONE;
}

void queue_print(struct queue *queue)
{
    size_t i = queue->start, upto = (queue->start + queue->count) % QUEUE_MAX;
    if (queue->count > 0) {
        do {
            printf("%" PROJ_ELEM_FMT, queue->array[i++]);
            if (i >= QUEUE_MAX) i = 0;
        } while (i != upto);
    }
}

