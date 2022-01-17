#include "list.h"

// functie de adaugat un serial in lista generica
void *add_serial(void *list, void *data, int *poz) {
    plist node = (plist) calloc(2, sizeof(list));
    
    node->data = data;
    *poz = 1;
    if (list == NULL) {
        list = (void *)node;
    }else if (SER(data)->rating >= SERIAL(list)->rating) {
        if (SER(data)->rating == SERIAL(list)->rating) {
            if (strcmp(SERIAL(list)->name, SER(data)->name) < 0) {
                node->next = ((plist)list)->next;
                ((plist)list)->next = node;
                (*poz)++;   
            } else {
                node->next = list;
                list = (void *)node;    
            }
        } else {
            node->next = list;
            list = (void *)node;
        }    
    } else {
        plist aux = (plist)list;
        
        (*poz)++;
        while (aux->next && SER(data)->rating < SERIAL(aux->next)->rating) {
            aux = aux->next;
            (*poz)++;
        }
        while (aux->next) {
            if (SER(data)->rating == SERIAL(aux->next)->rating) {
                if (strcmp(SERIAL(aux->next)->name, SER(data)->name) < 0) {
                    aux = aux->next;
                    (*poz)++;
                } else {
                    break;
                }
            } else {
                break;
            }       
        }
        node->next = aux->next;
        aux->next = node;
    }
    return (void *)list;
}

// functie de adaugat un serial in lista top
void *add_top(void *list, void *data)
{
    plist node = (plist) calloc(2, sizeof(list));
    int poz = SER(data)->id, i = 0;
    
    node->data = data;
    if (list == NULL) {
        list = (void *)node;
    } else if (poz == 1) {
        node->next = list;
        list = node;
    } else {
        plist aux = (plist)list;
        
        int i = 1;
        while (aux->next && i < poz - 1) {
            aux = aux->next;
            i++;
        }
        node->next = aux->next;
        aux->next = node;
    }
    plist n = (plist)list;
   
    while (n->next && i < 9) {
        n = n->next;
        i++;
    }
    if (n && i == 9) {
        plist del = n->next;
        n->next = NULL;
        freeL(del);
    }

    return (void *)list;
}

// caut un serial in lista si returnez un pointer catre acesta 
void *find_s(void *list, char *name) 
{   
    if (list == NULL)
        return NULL;
    plist aux = (plist)list;
    
    if (aux && strcmp(SERIAL(aux)->name, name) == 0) {        
        return ((pnode)aux)->data;
    }
    while (aux->next && strcmp(SERIAL(aux->next)->name, name) != 0)
        aux = aux->next;
    
    if (aux->next && strcmp(SERIAL(aux->next)->name, name) == 0)
        return ((pnode)aux->next)->data;
    return NULL;    
}

// caut serial in cele 4 liste
void *find_s1(void *l1, void *l2, void *l3, void *top, char *name)
{
    void *serial = NULL;

    serial = find_s(l1, name);
    if (serial)
        return serial;
    serial = find_s(l2, name);
    if (serial)
        return serial;
    serial = find_s(l3, name);
    if (serial)
        return serial;
    serial = find_s(top, name);
    if (serial)
        return serial;
    return NULL;    
}

// caut serial, returnez pointer catre el si il scot din lista
void *find_serial(void **list, char *name) 
{   
    if (*list == NULL)
        return NULL;
    plist aux = (plist)*list;
    
    if (aux && strcmp(SERIAL(aux)->name, name) == 0) {
        plist node = aux;
        pnode d = (pnode) calloc(2, sizeof(node));

        *list = aux->next;
        d->data = (pqueue)node->data;
        free(node);        
        return (void *)d;
    }
    while (aux->next && strcmp(SERIAL(aux->next)->name, name) != 0)
        aux = aux->next;
    
    if (aux->next && strcmp(SERIAL(aux->next)->name, name) == 0) {
        plist node = aux->next;
        pnode d = (pnode) calloc(2, sizeof(node));

        aux->next = aux->next->next;
        d->data = (pqueue)node->data;
        free(node);        
        return (void *)d;
    }
    return NULL;    
}

// caut serial in cele 4 liste
void *find(void **l1, void **l2, void **l3, void **top, char *name)
{
    void *serial = NULL;

    serial = find_serial(l1, name);
    if (serial)
        return serial;
    serial = find_serial(l2, name);
    if (serial)
        return serial;
    serial = find_serial(l3, name);
    if (serial)
        return serial;
    serial = find_serial(top, name);
    if (serial)
        return serial;
    return NULL;    
}

// sterg o lista
void freeL(void *list)
{
    plist aux = (plist)list;
   
    while (aux) {
        plist del = aux;
        aux = aux->next;
        
        FreeQq(del->data);
        free(del);
    }
}

// printez o lista
void printL(void *list, FILE *fp, char *l_t, char *position)
{   
    plist aux = (plist)list;
    
    fprintf(fp, "Categoria %s: [", position);
    while (aux) {
        if (aux->next)
            fprintf(fp, "(%s, %.1f), ", SERIAL(aux)->name, SERIAL(aux)->rating);
        else
            fprintf(fp, "(%s, %.1f)", SERIAL(aux)->name, SERIAL(aux)->rating);
        aux = aux->next;
    }
    fprintf(fp, "].\n");
}

