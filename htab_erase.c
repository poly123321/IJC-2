// htab_erase.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"
#include <string.h>
#include <stdlib.h>

// Zrusi zaznam se zadanym klicem z tabulky t
// Vraci true pokud byl zaznam nalezen a zrusen, jinak false
bool htab_erase(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *item = t->arr[index];
    struct htab_item *prev = NULL;

    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            if (prev == NULL)
                t->arr[index] = item->next; // rusime prvni v listu
            else
                prev->next = item->next;    // rusime prostredni/posledni

            free((char *)item->pair.key);
            free(item);
            t->size--;
            return true;
        }
        prev = item;
        item = item->next;
    }

    return false; // nenasli jsme
}
