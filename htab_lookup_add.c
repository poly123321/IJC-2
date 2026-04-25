// htab_lookup_add.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"
#include <string.h>
#include <stdlib.h>

// Vyhleda zaznam se zadanym klicem v tabulce t
// Pokud zaznam existuje, inkrementuje jeho hodnotu a vrati ukazatel na nej
// Pokud neexistuje, prida novy zaznam s hodnotou 1 a vrati ukazatel na nej
// Vraci NULL pri chybe alokace
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *item = t->arr[index];

    // hledame jestli uz zaznam existuje
    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            item->pair.value++;      // inkrementuj pri nalezu
            return &item->pair;
        }
        item = item->next;
    }

    // nenasli jsme -> vytvorime novy zaznam
    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL)
        return NULL;

    new_item->pair.key = strdup(key);
    if (new_item->pair.key == NULL) {
        free(new_item);
        return NULL;
    }

    new_item->pair.value = 1;   // prvni vyskyt

    new_item->next = t->arr[index];
    t->arr[index] = new_item;
    t->size++;

    return &new_item->pair;
}
