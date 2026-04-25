// htab_size.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"

// Vrati size tabulky
size_t htab_size(const htab_t *t) {
    return t->size;
}
