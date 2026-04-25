// htab_private.h
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#ifndef HTAB_PRIVATE_H__
#define HTAB_PRIVATE_H__

#include "htab.h"

// Jeden záznam v tabulce (linked list node)
struct htab_item {
    htab_pair_t pair;        // klíč + hodnota (veřejná část)
    struct htab_item *next;  // další položka ve stejném bucketu
};

// Kompletní definice tabulky (uživatel vidí jen "struct htab;")
struct htab {
    size_t size;             // počet záznamů celkem
    size_t arr_size;         // počet bucketů
    struct htab_item *arr[]; // flexible array member — pole ukazatelů
};

#endif


