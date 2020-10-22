/* using queue */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

enum queue_op { NQ, DQ };

void queue_print_error(enum queue_error error_kind)
{
    switch (error_kind) {
    case QUEUE_ERR_NONE: printf("ok"); break;
    case QUEUE_ERR_FULL: printf("queue full"); break;
    case QUEUE_ERR_EMPTY: printf("queue empty"); break;
    case QUEUE_ERR_NOMEMORY: printf("no memory"); break;
    }
}

int queue__try(struct queue *t, enum queue_op op, queue_elem value)
{
    enum queue_error error;
    if (op == DQ) {
        error = dequeue(t, &value);
        if (error == QUEUE_ERR_NONE)
            printf("dequeued %3d: ", value);
        else
            printf("can't dequeue: ");
    } else if (op == NQ) {
        error = enqueue(t, value);
        if (error == QUEUE_ERR_NONE)
            printf("enqueued %3d: ", value);
        else
            printf("can't enqueue: ");
    }
    queue_print_error(error);
    puts("");
    return error == QUEUE_ERR_NONE;
}

int main(void)
{
    enum queue_op ops[] = {
        NQ, NQ, NQ, DQ, NQ, DQ, DQ, DQ,
        DQ, NQ, NQ, NQ, NQ, NQ, DQ, DQ,
        NQ, NQ, NQ, NQ, NQ, NQ, DQ, DQ, 
        NQ, DQ, DQ, DQ, DQ
    };
    queue_elem values[] = { 1, 89, -34, 47, 22, 34, -62, -77, -20, 0, 16, -42, -68, -7, 3, 43 };
    struct queue *t = queue_new();
    size_t i, trials;
    queue_elem *value = values;
    trials = ARRAY_SIZE(ops);
    for (i = 0; i < trials; i++) {
        if (queue__try(t, ops[i], *value))
            if (ops[i] == NQ) value++;
        printf("::");
        queue_print(t);
        puts("");
    }
    queue_free(t);
    return 0;
}

