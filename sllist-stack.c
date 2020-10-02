/* stack data structure using singly linked list */

#include <stdio.h>
#include <stdlib.h>

#define STACK_IMPLEMENTATION

#include "stack.h"

struct stack_node {
    stack_elem value;
    struct stack_node *next;
};

struct stack {
    struct stack_node *top;
};

struct stack *stack_new(void)
{
    struct stack *stack = malloc(sizeof(struct stack));
    stack->top = NULL;
    return stack;
}

void stack_free(struct stack *stack)
{
    struct stack_node *tmp, *top = stack->top;
    while (top != NULL) {
        tmp = top->next;
        free(top);
        top = tmp;
    }
    free(stack);
}

enum stack_error stack_push(struct stack *stack, stack_elem elem)
{
    struct stack_node *new_node = malloc(sizeof(struct stack_node));
    if (!new_node) 
        return STACK_ERR_NOMEMORY;
    new_node->value = elem;
    new_node->next = stack->top;
    stack->top = new_node;
    return STACK_ERR_NONE;
}

enum stack_error stack_pop(struct stack *stack, stack_elem *elem)
{
    struct stack_node *new_top;
    if (stack->top == NULL) 
        return STACK_ERR_UNDERFLOW;
    *elem = stack->top->value;
    new_top = stack->top->next;
    free(stack->top);
    stack->top = new_top;
    return STACK_ERR_NONE;
}

void stack_print(struct stack *stack)
{
    struct stack_node *current = stack->top;
    while (current != NULL) {
        printf("%" PROJ_ELEM_FMT, current->value);
        current = current->next;
    }
}

