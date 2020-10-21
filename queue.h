/* queue functions prototype */
#ifndef     QUEUE_H
#define     QUEUE_H

#include "common.h"

typedef PROJ_ELEM_TYPE queue_elem;

enum queue_error {
    QUEUE_ERR_NONE,
    QUEUE_ERR_FULL,
    QUEUE_ERR_EMPTY,
    QUEUE_ERR_NOMEMORY
};

struct queue *queue_new(void);
void queue_free(struct queue *);

enum queue_error enqueue(struct queue *, queue_elem);
enum queue_error dequeue(struct queue *, queue_elem *);
void queue_print_error(enum queue_error);
void queue_print(struct queue *);

#endif   /* QUEUE_H */

