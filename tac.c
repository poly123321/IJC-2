#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *line;
    struct node *next;
} Node;

typedef struct list{
    Node *head;
    size_t size;
} List;

void list_ins_first(List *l, char *line){
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

void list_free(List *l){
    Node *current;
    Node *next;

    current = l->head;

    while (current != NULL){
        next = current->next;
        free(current->line);
        free(current);
        current = next;
    }

    l->head = NULL;
    l->size = 0;
}

void list_init(List *l){
    l->head = NULL;
    l->size = 0;
}

size_t list_size(List *l){
    return l->size;
}

void list_print(List *l){
    Node *current = l->head;
    while(current != NULL){
        printf("%s", current->line);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    List l;
    list_init(&l);
    
    int limit = -1;
    FILE *f = stdin; 
    

    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            
            limit = atoi(argv[i+1]);
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
    
    char buf[1024];

    int count = 0;
    int warning_printed = 0;

    while (fgets(buf, 1024, f) != NULL){
        if (limit != -1 && count >= limit) break;

            if (strchr(buf, '\n') == NULL && !feof(f)) {
                if (!warning_printed) {
                    fprintf(stderr, "Radek je prilis dlouhy, bude zkracen\n");
                    warning_printed = 1;
                }
                int c;
                while ((c = fgetc(f)) != '\n' && c != EOF);
                
            }    

            char *line = strdup(buf);

            if (line == NULL) {
                fprintf(stderr, "Nedostatek pameti\n");
                return 1;
            }
            list_ins_first(&l, line);
        count++;
    }
    
    list_print(&l);
    list_free(&l);
    
    if (f != stdin) fclose(f);
    return 0;
}
