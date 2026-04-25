// htab_for_each.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"

// Projde vsechny zaznamy v tabulce t a zavola na ne funkci f
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *item = t->arr[i];
        while (item != NULL) {
            f(&item->pair);
            item = item->next;
        }
    }
}
