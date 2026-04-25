// io.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include "io.h"
#include <stdio.h>
#include <ctype.h>


// Precte jedno slovo ze souboru f do pole s o maximalni delce max
// Z delsich slov nacte prvnich max-1 znaku, zbytek preskoci
// Pri prvnim prilis dlouhem slove vypise varovani na stderr (max 1 varovani)
// Vraci delku slova, nebo EOF pri konci souboru
int read_word(unsigned max, char s[max], FILE *f) {
    int c;
    unsigned len = 0;
    static int warning_printed = 0; 

    
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;

    if (c == EOF)
        return EOF;

    // cti znaky slova
    while (c != EOF && !isspace(c)) {
        if (len < max - 1) {
            s[len++] = c;
        } else {
            if (!warning_printed) {
                fprintf(stderr, "Slovo je prilis dlouhe, bude zkraceno\n");
                warning_printed = 1;
            }
        }
        c = fgetc(f);
    }

    s[len] = '\0';
    return (int)len;
}
