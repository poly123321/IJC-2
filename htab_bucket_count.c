// htab_bucket_count.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include "htab_private.h"

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}
