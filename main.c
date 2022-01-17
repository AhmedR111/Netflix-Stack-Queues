#include "list.h"

int main(int argc, char const *argv[])
{
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    // cele 4 liste pentru gestionarea categoriilor de seriale
    void *list_1 = NULL, *list_2 = NULL, *list_3 = NULL, *top = NULL;
    // coada watch_later 
    void *watch_later = NULL, *serial = NULL;
    // cele doua stive currently_watching si history
    void *currently_watching = NULL, *history = NULL;
    char command[10], position[20], name[33];
    int poz, min, total = 0;

    // prelucrez operatiile
    while (fscanf(in, "%s", command) != EOF) {
        if (strcmp("add", command) == 0) {
            void *serial = make_serial(in);
            if (SER(serial)->id == 1)
                list_1 = add_serial(list_1, serial, &poz);
            else if (SER(serial)->id == 2)
                list_2 = add_serial(list_2, serial, &poz);
            else
                list_3 = add_serial(list_3, serial, &poz);
            fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n", SER(serial)->name, poz);
        } else if (strcmp("add_sez", command) == 0) { 
            fscanf(in, "%s", name);

            void *serial = find_s1(list_1, list_2, list_3, top, name);
            if (serial == NULL)
                serial = find_w2(&watch_later, name);
            if (serial == NULL)
                serial = find_stack(&currently_watching, name);
            if (serial) {
                void *seasons = make_season(in, &total);
                pnode d = (pnode) calloc(1, sizeof(node));  
        
                d->data = (pqueue)seasons;
                enqueue(serial, (pnode)d);
                SER(serial)->time += total;
                fprintf(out, "Serialul %s are un sezon nou.\n", name);
            }
        } else if (strcmp("add_top", command) == 0) { 
            void *serial = make_serial(in);

            top = add_top(top, serial);
            printL(top, out, "top", "top10");
        } else if (strcmp("watch", command) == 0) {
            fscanf(in, "%s%d", name, &min);
            serial = find(&list_1, &list_2, &list_3, &top, name);
            if (serial == NULL)
                serial = find_w(&watch_later, name);
            if (serial == NULL)
                serial = find_stack2(&currently_watching, name);
            if (serial) {
                if (SER(((pnode)serial)->data)->time <= min) {
                    history = add_stack(history, serial);
                    fprintf(out, "Serialul %s a fost vizionat integral.\n", name);
                } else {
                    currently_watching = add_stack(currently_watching, serial);
                    SER(((pnode)serial)->data)->time -= min;
                }
            }
        } else if (strcmp("later", command) == 0) {
            fscanf(in, "%s", name);
            serial = find(&list_1, &list_2, &list_3, &top, name);
           
            if (serial) {
                watch_later = add_later(watch_later, serial);
                fprintf(out, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", name, SIZE(watch_later));  
            }
        } else if (strcmp("show", command) == 0) {
            fscanf(in, "%s", position);
            if (strcmp(position, "1") == 0)
                printL(list_1, out, "list", position);
            else if (strcmp(position, "2") == 0)
                printL(list_2, out, "list", position);
            else if (strcmp(position, "3") == 0)
                printL(list_3, out, "list", position);
            else if (strcmp(position, "later") == 0)
                print_later(watch_later, out);
            else if (strcmp(position, "top10") == 0)
                printL(top, out, "top", position);
            else if (strcmp(position, "watching") == 0)
                print_stack(currently_watching, out, "watching");            
            else if (strcmp(position, "history") == 0)
                print_stack(history, out, "history");
        }
    }
    // eliberez toata memoria
    if (currently_watching)
        free_stack(currently_watching);
    if (history)
        free_stack(history);
    freeL(list_1);
    freeL(list_2);
    freeL(list_3);
    freeL(top);
    if ((pqueue)watch_later)
        free_later(watch_later);
    fclose(in);
    fclose(out);
    return 0;
}