#include "stack.h"
#include "list.h"

// initializez o stiva
void *initStack(void *data)
{
    pstack a = (pstack) calloc(1, sizeof(stack));

    a->data = data;
    return (void *)a;
}

// functie de adugare in stiva
void push(void *a, void *node)
{
    if (HEAD(a) == NULL) {
        HEAD(a) = (pnode)node;
    } else {
        ((pnode)node)->next = HEAD(a);
        HEAD(a) = (pnode)node;
    }
}

// adaug in stiva un serial
void *add_stack(void *stack, void *serial)
{
    if (stack == NULL) {
        pdime size = (pdime) calloc(1, sizeof(dime));
       
        size->size = 0;
        stack = initStack(size);
    }
    push(stack, (pnode)serial);
    DIME(stack)++;

    return stack;
}

// scot din stiva un serial si returnez pointer catre el
void *pop(void *a)
{
    if (HEAD(a) == NULL)
        return NULL;
    pnode d = HEAD(a);
    
    HEAD(a) = HEAD(a)->next;
    return d;
}

// functie de inversat o stiva
void *reverse(void *stack) {
    void *s = NULL;
    
    if (stack == NULL)
        return NULL;
    while (HEAD(stack) != NULL) {
        void *serial = pop(stack);
    
        ((pnode)serial)->next = NULL;
        s = add_stack(s, serial);
    }
    free_stack(stack);
    return s;
}

// in functiile find caut un serial
// nu iterez prin stive ci imi formez noi stive
// prin operatii specifice pentru a obtine pointerul catre serial
void *find_stack(void **stack, char *name)
{
    void *s = NULL, *ser = NULL;
    
    if (*stack == NULL && HEAD(*stack) == NULL)
        return NULL;
    while (HEAD(*stack) != NULL){
        void *serial = pop(*stack);
    
        ((pnode)serial)->next = NULL;
        if (strcmp(SER(((pnode)serial)->data)->name, name) == 0)      
            ser = ((pnode)serial)->data;
        s = add_stack(s, serial);
    }
    free_stack(*stack);
    *stack = reverse(s);
    return ser;
}

void *find_stack2(void **stack, char *name)
{
    void *s = NULL, *ser = NULL;
    
    if (*stack == NULL)
        return NULL;
    while (HEAD(*stack) != NULL){
        void *serial = pop(*stack);
    
        ((pnode)serial)->next = NULL;
        if (strcmp(SER(((pnode)serial)->data)->name, name) == 0)      
            ser = serial;
        else
            s = add_stack(s, serial);
    }
    free_stack(*stack);
    *stack = reverse(s);
    return ser;
}

// functii de prelucrare functii pe stive
void PrelS(void *a, TF1 f)   
{  
    pnode aux = HEAD(a);                
  	
    for(; aux != NULL; aux = aux->next) 
    	f(aux);
}

void AfiS(TF1 AfiElem, void *a)
{
  	if (HEAD(a) != NULL)
        PrelS(a, AfiElem);
}


void PrelS2(void *a, TF2 f, void *b)   
{ 
    pnode aux = HEAD(a);                
  	
      for(; aux != NULL; aux = aux->next) 
    	f(aux, b);
}

void AfiS2(TF2 AfiElem, void *a, void *b)
{
  	if (HEAD(a) != NULL)
        PrelS2(a, AfiElem, b);
}

// printez o stiva
void print_stack(void *a, FILE *out, char *name)
{
    fprintf(out, "Categoria %s: [", name);
    if ((pstack)a)
        AfiS2(AfiP, a, out);
    fprintf(out, "].\n");
}

// sterg o stiva
void free_stack(void *stack)
{
    AfiS(AfiD, stack);
    pnode aux = HEAD(stack);

    while (aux) {
        pnode del = aux;
        
        aux = aux->next;
        free(del);
    }
    free(((pstack)stack)->data);
    free(stack);
}