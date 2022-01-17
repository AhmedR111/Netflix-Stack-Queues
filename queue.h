#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FUNCTII_
#define _FUNCTII_
  typedef void (*TF1)(void *);
  typedef void (*TF2)(void *, void *);
#endif

typedef struct serial {
    char name[33];
    int id;
    float rating;
    int nr_sezoane; //optional pentru ca il gasesc in coada
    int time; // timpul total al unui serial !!!! eu l am adaugat 
} *pserial, serial;

typedef struct node {
    void *data;  // pointer catre coada de tip sezon sau pointer catre durata episodului
    struct node *next;
} *pnode, node;
/*
    Din enunt se inelege ca un serial este o coada
    deci in coada se gaseste un pointer catre datele serialului
    si o sa am noduri cu sezoane care contin cozi de episoade 
*/
typedef struct {
    int size;
} *pdime, dime;

typedef struct queue {
    void *data; // pointer catre datele serialului din coada de sezoane sau pointer catre numarul de episoade din coada de episoade
    pnode front;
    pnode rear;
}  *pqueue, queue; 

#define SIZE(a) (((pdime)((pqueue)a)->data)->size)
#define TIME(a)  (((pdime)((pnode)a)->data)->size)
#define REAR(a)  (((pqueue)a)->rear)
#define FRONT(a)  (((pqueue)a)->front)
#define NAME(a) (((pserial)((pqueue)((pnode)a)->data)->data)->name)
#define RATING(a) (((pserial)((pqueue)((pnode)a)->data)->data)->rating)
#define SERIAL(l) (((pserial)((pqueue)((plist)l)->data)->data))
#define SER(l)   ((pserial)((pqueue)l)->data)

void *initQueue(void *data);
void enqueue(void *a, void *node);
void dequeue(void *a);
void *make_season(FILE *fp, int *total);
void *make_serial(FILE *fp);
void *add_later(void *watch_later, void *serial);
void PrelQ(void *a, TF1 f);
void PrelQ2(void *a, TF2 f, void *b);
void AfiQ(TF1 AfiElem, void *a);
void AfiQ2(TF2 AfiElem, void *a, void *b);
void AfiP(void *a, void *b);
void print_later(void *a, FILE *out);
void FreeQ(void *a);
void FreeQq(void *serial);
void AfiD(void *a);
void *find_w(void **watch_later, char *name);
void *find_w2(void **watch_later, char *name);
void free_later(void *watch_later);
void *front(void *a);

#endif