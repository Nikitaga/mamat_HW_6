#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Defining structs for the linked list and the linked list nodes
typedef struct linked_list_node linked_list_node;
typedef struct linked_list linked_list;

struct linked_list {

	linked_list_node* head;
	linked_list_node* tail;
};

struct linked_list_node {

	char* word;
	bool unused;
	linked_list_node* next;
};


// Input related functions. We got them this way!
char* readline();
char** split_string(char*);


// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine,
				   int note_count, char** note);

// Sub-functions of checkMagazine. Full explanation below.
linked_list_node* insert_head(linked_list_node* list, char* data);
bool search_word(linked_list_node* node, char* data);
void free_linked_list(linked_list_node* node);

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



// Checks if a note can be compiled from the magazines by making a linked list
// from the magazine words and adding a flag for used/unused status per node
void checkMagazine(int magazine_count, char** magazine,
				   int note_count, char** note) {

	struct linked_list* magazine_list =
			(struct linked_list*)malloc(sizeof(linked_list));

	for (int i = 0; i < magazine_count; i++) {
		linked_list_node* node =
				insert_head(magazine_list->head, *(magazine + i));
		magazine_list->head = node;
	};

	for (int i = 0; i < note_count; i++) {
			if (!search_word(magazine_list->head, *(note + i))) {
				printf("No");
				return;
			}
		};
	printf("Yes");
	free_linked_list(magazine_list->head);
	free(magazine_list);
};


// Insert a new node in front of the linked list
linked_list_node* insert_head(linked_list_node* list, char* data) {

	linked_list_node* node = malloc(sizeof(linked_list_node));

	node->word = data;
	node->unused = true;
	node->next = list;
	return node;
}


// Check if a word exists and is still unused in the magazines
bool search_word(linked_list_node* node, char* data){
	while (node != NULL) {
		if (!strcmp(data, node->word) && node->unused == true){
			node->unused = false;
			return true;
		}
		node = node->next;
	}
	return false;
}

// Free all the nodes
void free_linked_list(linked_list_node* node){
	while (node != NULL) {
		linked_list_node* temp = node;
		node = node->next;
		free(temp);
	}
}
