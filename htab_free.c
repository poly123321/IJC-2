// htab_free.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

// zrusi vsechny zaznamy a uvolni pamet tabulky
void htab_free(htab_t *t) {
    htab_clear(t);
    free(t);
}
