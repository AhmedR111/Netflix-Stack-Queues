#include "queue.h"

// initializare coada
void *initQueue(void *data)
{
    pqueue a = (pqueue) calloc(1, sizeof(queue));

    a->data = data;
    return (void *)a;
}

// adaugare in coada
void enqueue(void *a, void *node)
{
    if (REAR(a) == NULL) {
        FRONT(a) = (pnode)node; 
        REAR(a) = (pnode)node;
    } else {
        REAR(a)->next = (pnode)node;
        REAR(a) = (pnode)node;
    }
}

// scot din coada 
void dequeue(void *a) {
    if (FRONT(a) == NULL)
        return;
    pnode del = FRONT(a);
    
    FRONT(a) = FRONT(a)->next;
    free(del->data);
    free(del);
}

// scot din coada si returnez primul element
void *front(void *a)
{
    if (FRONT(a) == NULL)
        return NULL;
    pnode d = FRONT(a);
    
    FRONT(a) = FRONT(a)->next;
    return d;
}

// formez o coada de sezoane
void *make_season(FILE *fp, int *total) {
    pdime size = (pdime) calloc(1, sizeof(dime));
    int n, time;
    
    size->size = 0;
    void *a = initQueue(size);
    
    *total = 0;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        pdime s = (pdime) calloc(1, sizeof(dime));
        pnode d = (pnode) calloc(1, sizeof(node));

        fscanf(fp, "%d", &time);
        *total += time;
        s->size = time;
        d->data = (pdime)s;
        enqueue(a, (pnode)d);
        SIZE(a)++;
    }
    return a;
}

// formez o coada de seriale
void *make_serial(FILE *fp) {
    pserial ser = (pserial) calloc(1, sizeof(serial));
    char name[32];
    int id, nr_seasons, total = 0;
    float rating;

    fscanf(fp, "%d%s%f%d", &id, name, &rating, &nr_seasons);
    strcpy(ser->name, name);
    ser->id = id;
    ser->nr_sezoane = nr_seasons;
    ser->rating = rating;
    ser->time = 0;
    void *serial = initQueue(ser);
    
    for (int i = 0; i < nr_seasons; i++) {
        pnode d = (pnode) calloc(1, sizeof(node));
        void *a = make_season(fp, &total);  
        
        ser->time += total;
        total = 0;
        d->data = (pqueue)a;
        enqueue(serial, (pnode)d);
    }
    return (void *)serial;
}

// formez o coada watch_later
void *add_later(void *watch_later, void *serial)
{
    if (watch_later == NULL) {
        pdime size = (pdime) calloc(1, sizeof(dime));
        size->size = 0;
        watch_later = initQueue(size);
    }
    enqueue(watch_later, (pnode)serial);
    SIZE(watch_later)++;
    
    return watch_later;
}

// functii de prelucrat fuctii pe coada
// ca in laborator
void PrelQ(void *a, TF1 f)   
{  
    pnode aux = FRONT(a);                
  	
    for(; aux != NULL; aux = aux->next) 
    	f(aux);
}

void PrelQ2(void *a, TF2 f, void *b)   
{ 
    pnode aux = FRONT(a);                
  
  	for(; aux != NULL; aux = aux->next) 
    	f(aux, b);
}

void AfiQ(TF1 AfiElem, void *a)
{
  	if (REAR(a) != NULL)
        PrelQ (a, AfiElem);
}

void AfiQ2(TF2 AfiElem, void *a, void *b)
{
  	if (REAR(a) != NULL)
        PrelQ2(a, AfiElem, b);
}

void AfiD(void *a)
{   
	FreeQq(((pnode)a)->data);    
}

void AfiP(void *a, void *b)
{   
    FILE *out = b;

    if (((pnode)a)->next) {
	    fprintf(out, "(%s, ", NAME(a));
	    fprintf(out, "%.1f), ", RATING(a));
    } else {
        fprintf(out, "(%s, ", NAME(a));
	    fprintf(out, "%.1f)", RATING(a));
    }
}

// afisare coada watch_later
void print_later(void *a, FILE *out)
{
    fprintf(out, "Categoria later: [");
    if ((pqueue)a)
        AfiQ2(AfiP, a, out);
    fprintf(out, "].\n");
}

// caut un serial si returnez un pointer catre acesta
// in caz ca nu exista returnez Null
void *find_w(void **watch_later, char *name)
{
    void *queue = NULL, *ser = NULL;
    
    if (*watch_later == NULL)
        return NULL;
    while (FRONT(*watch_later) != NULL){
        void *serial = front(*watch_later);
        ((pnode)serial)->next = NULL;
        if (strcmp(SER(((pnode)serial)->data)->name, name) == 0)
            ser = serial;
        else    
            queue = add_later(queue, serial);
    }
    free_later(*watch_later);
    *watch_later = queue;

    return ser;
}
// caut un serial, returnez pointer catre acesta si il scot din coada.
// la ambele functii find nu iterez prin coada ci folosesc functia 
// front de scoatere a primului element si imi creez alta coada
void *find_w2(void **watch_later, char *name)
{
    void *queue = NULL, *ser = NULL;
   
    if (*watch_later == NULL)
        return NULL;
    while (FRONT(*watch_later) != NULL){
        void *serial = front(*watch_later);
        ((pnode)serial)->next = NULL;
        if (strcmp(SER(((pnode)serial)->data)->name, name) == 0)      
            ser = ((pnode)serial)->data;
        queue = add_later(queue, serial);
    }
    free_later(*watch_later);
    *watch_later = queue;

    return ser;
}

// functie auziliara de sters o coada
void FreeQ(void *a)
{
    while(FRONT(a) != NULL) {
        dequeue(a);        
    }
    free(((pqueue)a)->data);
    free(a);
}

// functie de stergere a cozii
void FreeQq(void *serial)
{
    pnode aux = FRONT(serial); 
    while (aux) {
        pnode del = aux;
        
        aux = aux->next; 
        FreeQ(del->data);   
        free(del);
    }
    free(((pqueue)serial)->data);
    free(serial);
}

// functie de stergere a cozii watch later
void free_later(void *watch_later)
{
    AfiQ(AfiD, watch_later);
    pnode aux = FRONT(watch_later);

    while (aux) {
        pnode del = aux;
        
        aux = aux->next;
        free(del);
    }
    free(((pqueue)watch_later)->data);
    free(watch_later);
}