#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define LINKSCOUNT 27

typedef struct node {
    bool is_word;
    struct node* links[LINKSCOUNT];
} node;

node *n;       
int node_count;

void free_mem(node*);

bool check(const char* word) {
    node* current_node = n;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = tolower(word[i]) - 'a';
        current_node = current_node->links[index];
        if (current_node == NULL) {
            return false;
        }
    }
    return current_node->is_word;
}

bool load(const char* dictionary) {
    FILE *f = fopen(dictionary, "r");
    char word[LENGTH+1];

    if (f == NULL) {
        return false;
    }

    n = malloc(sizeof(node));
    n->is_word = false;

    for (int i = 0; i < LINKSCOUNT; i++) {
        n->links[i] = NULL;
    } 
    while(fscanf(f, "%s\n", word) != EOF)
    {
        node* current_node = n;
        
        for (int i = 0; word[i] != '\0'; i++) {
            int index = tolower(word[i]) - 'a';
            
            if (current_node->links[index] == NULL)
            {
                node* new_node = malloc(sizeof(node));
                new_node->is_word = false;
                for (int j = 0; j < LINKSCOUNT; j++) {
                    new_node->links[j] = NULL;
                }
                current_node->links[index] = new_node;
            }
            current_node = current_node->links[index];
        }
        current_node->is_word = true;
        node_count++;
    }
    fclose(f);
    return true;
}

unsigned int size(void) {
    return node_count;
}

bool unload(void) {
    free_mem(n);
    return true;
}

void free_mem(node* n) {
    for (int i = 0; i < LINKSCOUNT; i++) {
        if (n->links[i] != NULL) {
            free_mem(n->links[i]);
        }
    }
    free(n);
}

