// tac.c
// Jan Polasek, FSI VUT, IJC-DU2, 2026

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

// Uzel seznamu reprezentujici jeden radek
typedef struct node {
    char *line;
    struct node *next;
} Node;

// Seznam dynamicky alokovaných radku
typedef struct list {
    Node *head;
    size_t size;
} List;

// Vlozi radek na zacatek seznamu
void list_ins_first(List *l, char *line) {
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        fprintf(stderr, "Nedostatek pameti\n");
        return;
    }

    new_node->line = line;
    new_node->next = l->head;
    l->head = new_node;
    l->size++;
}

// Uvolni vsechny uzly seznamu i jejich obsah
void list_free(List *l) {
    Node *current = l->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->line);
        free(current);
        current = next;
    }
    l->head = NULL;
    l->size = 0;
}

// Inicializuje prazdny seznam
void list_init(List *l) {
    l->head = NULL;
    l->size = 0;
}

// Vraci pocet uzlu v seznamu
size_t list_size(List *l) {
    return l->size;
}

// Vytiskne vsechny radky seznamu
void list_print(List *l) {
    Node *current = l->head;
    while (current != NULL) {
        printf("%s", current->line);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    List l;
    list_init(&l);

    int limit = -1;    
    FILE *f = stdin;

    // zpracovani argumentu prikazove radky
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            limit = atoi(argv[i + 1]);
            if (limit < 0) {
                fprintf(stderr, "Chybny parametr -l\n");
                return 1;
            }
            i++;
        } else {
            f = fopen(argv[i], "r");
            if (f == NULL) {
                fprintf(stderr, "Nelze otevrit soubor\n");
                return 1;
            }
        }
    }

    char buf[MAX_LINE_LEN];
    int count = 0;
    int warning_printed = 0;

    while (fgets(buf, MAX_LINE_LEN, f) != NULL) {
        if (limit != -1 && count >= limit) break;

        // detekce prilis dlouheho radku
        if (strchr(buf, '\n') == NULL && !feof(f)) {
            if (!warning_printed) {
                fprintf(stderr, "Radek je prilis dlouhy, bude zkracen\n");
                warning_printed = 1;
            }
         
            int c;
            while ((c = fgetc(f)) != '\n' && c != EOF)
                ;
        }

        size_t len = strlen(buf) + 1;
        char *line = malloc(len);
        if (line == NULL) {
            fprintf(stderr, "Nedostatek pameti\n");
            list_free(&l);
            if (f != stdin) fclose(f);
            return 1;
        }
        strcpy(line, buf);

        list_ins_first(&l, line);
        count++;
    }

    list_print(&l);
    list_free(&l);

    if (f != stdin) fclose(f);
    return 0;
}