/* using stack */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

enum stack_op { PUSH, POP };

void stack_print_error(enum stack_error error_kind)
{
    switch (error_kind) {
    case STACK_ERR_NONE: printf("ok"); break;
    case STACK_ERR_UNDERFLOW: printf("stack underflow"); break;
    case STACK_ERR_OVERFLOW: printf("stack overflow"); break;
    case STACK_ERR_NOMEMORY: printf("no memory"); break;
    }
}

int stack__try(struct stack *t, enum stack_op op, stack_elem value)
{
    enum stack_error error;
    if (op == POP) {
        error = stack_pop(t, &value);
        if (error == STACK_ERR_NONE)
            printf("popped %3d: ", value);
        else
            printf("can't pop: ");
    } else if (op == PUSH) {
        error = stack_push(t, value);
        if (error == STACK_ERR_NONE)
            printf("pushed %3d: ", value);
        else
            printf("can't push: ");
    }
    stack_print_error(error);
    puts("");
    return error == STACK_ERR_NONE;
}

int main(void)
{
    enum stack_op ops[] = {
        PUSH, PUSH, POP, PUSH, PUSH, POP, POP, POP, 
        POP, PUSH, PUSH, PUSH, PUSH, POP, PUSH, PUSH, 
        PUSH, PUSH, PUSH, PUSH, POP, POP, POP, PUSH, 
        POP, POP, PUSH, POP
    };
    stack_elem values[] = {7, -4, 17, 42, -18, -83, 35, 47, 53, -19, 22, -9, 0, -49, 51};
    struct stack *t = stack_new();
    size_t i, trials;
    stack_elem *value = values;
    trials = ARRAY_SIZE(ops);
    for (i = 0; i < trials; i++) {
        if (stack__try(t, ops[i], *value))
            if (ops[i] == PUSH) value++;
        printf("::");
        stack_print(t);
        puts("");
    }
    stack_free(t);
    return 0;
}

