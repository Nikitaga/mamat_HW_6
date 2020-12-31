#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Defining structs for the linked list and the linked list nodes */
typedef struct linked_list_node linked_list_node_t;
typedef struct linked_list linked_list_t;

/* linked list, includes:
 * head - pointer to the head node
 * tail - pointer to the tail node */
struct linked_list {
    linked_list_node_t* head;
    linked_list_node_t* tail;
};

/* linked list node, includes:
 * word - a word from the input
 * unused - marks if the word in the node has already been used
 * next - pointer to the next node in the linked list */
struct linked_list_node {
    char* word;
    int unused;
    linked_list_node_t* next;
};

/* Input related functions. We got them this way! */
char* readline();
char** split_string(char*);


/**
 * @brief Checks if a note can be compiled from the magazines. Makes a linked
 *        list of the magazine, and checks for the required words in the list
 * @param magazine_count - magazine words count
 * @param magazine - a pointer to the magazine's word list
 * @param note_count - note words count
 * @param note - a pointer to the note's word list
 * @note - prints "Yes" if the note can be compiled, "No" otherwise.
 * */
void checkMagazine(int magazine_count,
                   char** magazine,
                   int note_count,
                   char** note);


/**
 * @brief Inserts a new node in the head of the linked list.
 * @param list - a pointer to the current head node
 * @param data - a pointer to the input word
 * @return - a new node at the head of the list
 * @note - sets word = data, unused = 1, next = pointer to the next node
 * */
linked_list_node_t* insert_head(linked_list_node_t *list, char *data);

/**
 * @brief Inserts a new node in the head of the linked list.
 * @param node - a pointer to the current head node
 * @param data - a pointer to the input word
 * @return - 1 if the word is available, 0 otherwise
 * @note - when returning 1, change the relevant node status to unused = 0
 * */
int search_word(linked_list_node_t *node, char *data);

/**
 * @brief Free all the nodes in the linked list.
 * @param node - a pointer to the current head node
 * @param data - a pointer to the input word
 * @note - no return value. Frees the memory allocation of all the nodes
 * */
void free_linked_list(linked_list_node_t *node);

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}



/* Checks if a note can be compiled from the magazines*/
void checkMagazine(int magazine_count,
                   char **magazine,
                   int note_count,
                   char **note) {

    struct linked_list *magazine_list =
            (struct linked_list*)malloc(sizeof(linked_list_t));

    for (int i = 0; i < magazine_count; i++) {
        linked_list_node_t *node =
            insert_head(magazine_list->head, *(magazine + i));
		magazine_list->head = node;
    }

    for (int i = 0; i < note_count; i++) {
        if (search_word(magazine_list->head, *(note + i))) {
                printf("No");
                break;
        };
        if (note_count -1 == i) {
        	printf("Yes");
        }
    }
    free_linked_list(magazine_list->head);
    free(magazine_list);
}


/* Inserts a new node in the head of the linked list.*/
linked_list_node_t *insert_head(linked_list_node_t *list, char *data) {

    linked_list_node_t *node = malloc(sizeof(linked_list_node_t));

    node->word = data;
    node->unused = 1;
    node->next = list;
    return node;
}


/* Check if a word exists and is still unused in the magazines*/
int search_word(linked_list_node_t *node, char *data){
    while (node != NULL) {
        if (!strcmp(data, node->word) && node->unused == true){
            node->unused = 0;
            return 0;
        }
        node = node->next;
    }
    return 1;
}

/* Free all the nodes */
void free_linked_list(linked_list_node_t *node){
    while (node != NULL) {
        linked_list_node_t *temp = node;
        node = node->next;
        free(temp);
	}
}
