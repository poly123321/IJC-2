// htab_hash_function.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "htab.h"
#include <stdint.h>


//Hash funkce
size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 0;
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}
