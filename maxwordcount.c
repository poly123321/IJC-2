// maxwordcount.c
// Jan Polasek, FSI VUT, IJC-DU2

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define MAX_WORD_LEN 100

#define HTAB_SIZE 1024

// Podmineny preklad vlastni hash funkce
#ifdef MY_HASH_FUNCTION
size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 0;
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 31 * h + *p; // jina varianta hash funkce
    return h;
}
#endif

// pomocna funkce pro htab_for_each - hleda maximum
static unsigned global_max = 0;

void find_max(htab_pair_t *pair) {
    if (pair->value > global_max)
        global_max = pair->value;
}

// pomocna funkce pro htab_for_each - tiskne nejcastejsi slova
void print_max(htab_pair_t *pair) {
    if (pair->value == global_max)
        printf("%s\t%u\n", pair->key, pair->value);
}

int main(void) {
    htab_t *t = htab_init(HTAB_SIZE);
    if (t == NULL) {
        fprintf(stderr, "Chyba: nelze alokovat tabulku\n");
        return 1;
    }

    char word[MAX_WORD_LEN];
    int len;

    // cti slova ze stdin
    while ((len = read_word(MAX_WORD_LEN, word, stdin)) != EOF) {
        if (len == 0)
            continue;

        htab_pair_t *pair = htab_lookup_add(t, word);
        if (pair == NULL) {
            fprintf(stderr, "Chyba: nelze alokovat zaznam\n");
            htab_free(t);
            return 1;
        }
    }

    // najdi maximum a vytiskni nejcastejsi slova
    htab_for_each(t, find_max);
    htab_for_each(t, print_max);

    htab_free(t);
    return 0;
}
