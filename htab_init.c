// htab_init.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <string.h>


// Konstruktor tabulky
htab_t *htab_init(size_t n) {
    htab_t *t = malloc(sizeof(htab_t) + n * sizeof(struct htab_item *));
    if (t == NULL)
        return NULL;

    t->size = 0;
    t->arr_size = n;

   
    for (size_t i = 0; i < n; i++)
        t->arr[i] = NULL;

    return t;
}
