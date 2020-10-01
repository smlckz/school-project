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
            printf("popped %d: ", value);
        else
            printf("unable to pop: ");
    } else {
        value = (rand() & 0xFF) ^ 0xFF;
        error = stack_push(t, value);
        if (error == STACK_ERR_NONE)
            printf("pushed %d: ", value);
        else
            printf("unable to push: ");
    }
    stack_print_error(error);
    puts("");
}

int main(void)
{
    struct stack *t = stack_new();
    size_t i, trials;
    srand(PROJ_RAND_SEED);
    trials = rand() & 0x7F;
    for (i = 0; i < trials; i++) {
        stack__try(t, rand() % 2);
        printf("stack:\n===\n");
        stack_print(t);
        printf("\n===\n");
    }
    stack_free(t);
    return 0;
}

