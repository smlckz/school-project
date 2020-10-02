/* using stack */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void stack__try(struct stack *t, int coin_toss)
{
    enum stack_error error;
    int value;
    if (coin_toss) {
        error = stack_pop(t, &value);
        if (error == STACK_ERR_NONE)
            printf("popped %3d: ", value);
        else
            printf("can't pop: ");
    } else {
        value = (rand() & 0xFF) ^ 0xFF;
        error = stack_push(t, value);
        if (error == STACK_ERR_NONE)
            printf("pushed %3d: ", value);
        else
            printf("can't push: ");
    }
    stack_print_error(error);
    puts("");
}

int main(void)
{
    struct stack *t = stack_new();
    size_t i, trials;
    srand(PROJ_RAND_SEED);
    trials = rand() & 0x5F;
    for (i = 0; i < trials; i++) {
        stack__try(t, rand() % 2);
        printf("::");
        stack_print(t);
        puts("");
    }
    stack_free(t);
    return 0;
}

