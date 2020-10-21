/* queue implemented using singly linked list */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct queue_node {
    queue_elem value;
    struct queue_node *next;
};

struct queue {
    struct queue_node *start, *end;
};

struct queue *queue_new(void)
{
    struct queue *queue = malloc(sizeof(struct queue));
    queue->start = NULL;
    queue->end = NULL;
    return queue;
}

void queue_free(struct queue *queue)
{
    struct queue_node *tmp, *current = queue->start;
    while (current != NULL) {
        tmp = current->next;
        current = tmp;
    }
    free(queue);
}

enum queue_error enqueue(struct queue *queue, queue_elem elem)
{
    struct queue_node *new_node = malloc(sizeof(struct queue_node));
    if (!new_node)
        return QUEUE_ERR_NOMEMORY;
    new_node->value = elem;
    new_node->next = NULL;
    if (queue->end != NULL)
        queue->end->next = new_node;
    queue->end = new_node;
    if (queue->start == NULL)
        queue->start = new_node;
    return QUEUE_ERR_NONE;
}

enum queue_error dequeue(struct queue *queue, queue_elem *elem)
{
    struct queue_node *first;
    if (queue->start == NULL)
        return QUEUE_ERR_EMPTY;
    first = queue->start;
    if (queue->start == queue->end)
        queue->end = NULL;
    queue->start = queue->start->next;
    *elem = first->value;
    free(first);
    return QUEUE_ERR_NONE;
}

void queue_print(struct queue *queue)
{
    struct queue_node *current = queue->start;
    while (current != NULL) {
        printf("%" PROJ_ELEM_FMT, current->value);
        current = current->next;
    }
}

