#ifndef _STACK_H_
#define _STACK_H_

#include "queue.h"

typedef struct stack {
    void *data;
    pnode head;
} *pstack, stack; 

#define HEAD(a) (((pstack)a)->head)
#define DIME(a) (((pdime)((pstack)a)->data)->size)

void *add_stack(void *stack, void *serial);
void print_stack(void *a, FILE *out, char *name);
void watch(void *stack, void *history, void *ser, int min, char *name, FILE *out);
void free_stack(void *stack);
void *find_stack(void **stack, char *name);
void *find_stack2(void **stack, char *name);
void *reverse(void *stack);
#endif