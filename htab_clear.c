// htab_clear.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

// Zrusi vsechny zaznamy v tabulce t, tabulka zustane prazdna
void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *item = t->arr[i];
        while (item != NULL) {
            struct htab_item *next = item->next;
            free((char *)item->pair.key); 
            free(item);
            item = next;
        }
        t->arr[i] = NULL;
    }
    t->size = 0;
}
