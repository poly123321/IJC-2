// htab_find.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"
#include <string.h>


// Vyhleda zaznam se zadanym klicem v tabulce t
// Vraci ukazatel na zaznam, nebo NULL pokud nebyl nalezen
htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *item = t->arr[index];

    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0)
            return &item->pair;
        item = item->next;
    }

    return NULL;
}
