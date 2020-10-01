/* queue implemented using static array */

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_IMPLEMENTATION

#include "queue.h"

#define QUEUE_MAX PROJ_ARRAY_MAX

struct queue {
    int divided;
    size_t start, end;
    queue_elem array[QUEUE_MAX];
};

struct queue *queue_new(void)
{
    struct queue *queue = malloc(sizeof(struct queue));
    queue->divided = 0;
    queue->start = 0;
    queue->end = 0;
    return queue;
}

void queue_free(struct queue *queue)
{
    free(queue);
}

enum queue_error enqueue(struct queue *queue, queue_elem elem)
{
    if (queue->divided && (queue->start == queue->end)) 
        return QUEUE_ERR_FULL;
    queue->array[queue->end++] = elem;
    if (queue->end >= QUEUE_MAX) {
        queue->end = 0;
        queue->divided ^= 1;
    }
    return QUEUE_ERR_NONE;
}

enum queue_error dequeue(struct queue *queue, queue_elem *elem)
{
    if (!queue->divided && (queue->start == queue->end))
        return QUEUE_ERR_EMPTY;
    *elem = queue->array[queue->start++];
    if (queue->start >= QUEUE_MAX) {
        queue->start = 0;
        queue->divided ^= 1;
    }
    return QUEUE_ERR_NONE;
}

void queue_print(struct queue *queue)
{
    size_t i = queue->start;
    if (queue->divided || (queue->start != queue->end)) {
        do {
            printf("%" PROJ_ELEM_FMT "\t", queue->array[i++]);
            if (i >= QUEUE_MAX) i = 0;
        } while (i != queue->end);
    }
}

