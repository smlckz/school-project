/* using queue */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void queue__try(struct queue *t, int coin_toss)
{
    enum queue_error error;
    int value;
    if (coin_toss) {
        error = dequeue(t, &value);
        if (error == QUEUE_ERR_NONE)
            printf("dequeued %d: ", value);
        else
            printf("unable to dequeue: ");
    } else {
        value = (rand() & 0xFF) ^ 0xFF;
        error = enqueue(t, value);
        if (error == QUEUE_ERR_NONE)
            printf("enqueued %d: ", value);
        else
            printf("unable to enqueue: ");
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
        printf("queue:\n===\n");
        queue_print(t);
        printf("\n===\n");
    }
    queue_free(t);
    return 0;
}

