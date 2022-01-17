#ifndef _LIST_H_
#define _LIST_H_

#include "queue.h"
#include "stack.h"
//Lista pentru cele 4 categorii 
typedef struct list {
    void *data;
    struct list *next;
} *plist, list;

void *add_serial(void *list, void *data, int *poz);
void *add_season(void *list, char *name, FILE *fp);
void *find_serial(void **list, char *name);
void *add_top(void *list, void *data);
void *find(void **l1, void **l2, void **l3, void **top, char *name);
void *find_s1(void *l1, void *l2, void *l3, void *top, char *name);
void freeL(void *list);
void printL(void *list, FILE *fp, char *l_t, char *position);

#endif
