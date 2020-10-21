/* using queue */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void queue_print_error(enum queue_error error_kind)
{
    switch (error_kind) {
    case QUEUE_ERR_NONE: printf("ok"); break;
    case QUEUE_ERR_FULL: printf("queue full"); break;
    case QUEUE_ERR_EMPTY: printf("queue empty"); break;
    case QUEUE_ERR_NOMEMORY: printf("no memory"); break;
    }
}

void queue__try(struct queue *t, int coin_toss)
{
    enum queue_error error;
    int value;
    if (coin_toss) {
        error = dequeue(t, &value);
        if (error == QUEUE_ERR_NONE)
            printf("dequeued %3d: ", value);
        else
            printf("can't dequeue: ");
    } else {
        value = (rand() & 0xFF) ^ 0xFF;
        error = enqueue(t, value);
        if (error == QUEUE_ERR_NONE)
            printf("enqueued %3d: ", value);
        else
            printf("can't enqueue: ");
    }
    queue_print_error(error);
    puts("");
}

int main(void)
{
    struct queue *t = queue_new();
    size_t i, trials;
    srand(PROJ_RAND_SEED);
    trials = rand() & 0x7F;
    for (i = 0; i < trials; i++) {
        queue__try(t, rand() % 2);
        printf("::");
        queue_print(t);
        puts("");
    }
    queue_free(t);
    return 0;
}

