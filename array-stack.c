/* stack implemented from static array */

#include <stdio.h>
#include <stdlib.h>

#define STACK_IMPLEMENTATION

#include "stack.h"

#define STACK_MAX PROJ_ARRAY_MAX

struct stack {
    long top;
    stack_elem array[STACK_MAX];
};

struct stack *stack_new(void)
{
    struct stack *stack = malloc(sizeof(struct stack));
    stack->top = -1;
    return stack;
}

void stack_free(struct stack *stack)
{
    free(stack);
}

enum stack_error stack_push(struct stack *stack, stack_elem elem)
{
    if ((stack->top + 1) >= STACK_MAX)
        return STACK_ERR_OVERFLOW;
    stack->array[++stack->top] = elem;
    return STACK_ERR_NONE;
}

enum stack_error stack_pop(struct stack *stack, stack_elem *elem)
{
    if (stack->top == -1)
        return STACK_ERR_UNDERFLOW;
    *elem = stack->array[stack->top--];
    return STACK_ERR_NONE;
}

void stack_print(struct stack *stack)
{
    long i;
    for (i = stack->top; i >= 0; i--) {
        printf("%" PROJ_ELEM_FMT, stack->array[i]);
    }
}

