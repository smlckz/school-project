/* stack functions prototypes */
#ifndef     STACK_H
#define     STACK_H

#include "common.h"

typedef PROJ_ELEM_TYPE stack_elem;

enum stack_error {
    STACK_ERR_NONE,
    STACK_ERR_OVERFLOW,
    STACK_ERR_UNDERFLOW,
    STACK_ERR_NOMEMORY
};

struct stack *stack_new(void);
void stack_free(struct stack *);

enum stack_error stack_push(struct stack *, stack_elem);
enum stack_error stack_pop(struct stack *, stack_elem *);
void stack_print_error(enum stack_error);
void stack_print(struct stack *);

#endif   /* STACK_H */

