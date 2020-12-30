#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	char *word;
    int num_of_words;
    struct Node *next;
} node;

char* readline();
char** split_string(char*);
void print_list(struct Node* head);
// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note);

//This function add node to the end of linked list if the word is not in the list
//or add 1 to the sum of the words in the list
void append_node(struct Node **head, char *word, int word_size);

//This function free all the allocated memory in the list and destroy it
void destroy_list(struct Node **head);

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

void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {

	//start creating magazine's words list
	int idx = 0;
    struct Node *magazine_head = (struct Node*)malloc(sizeof(struct Node));
    if (magazine_head == NULL) {
        printf("Failed to create magazine_node\n");
        return;
    }

    magazine_head->word = NULL;
    magazine_head->num_of_words = 0;
    magazine_head->next = NULL;

    for(int i = 0; i < magazine_count; ++i) {
        int word_size = 0;
        char *start_of_word = *(magazine) + idx;
        while (*((*magazine) + idx) != '\0') {
            ++word_size;
            ++idx;
        }

        append_node(&magazine_head, start_of_word, word_size);
        ++idx;
    }

    //start creating note's words list
    idx = 0;
    struct Node *note_head = (struct Node*)malloc(sizeof(struct Node));
    if (note_head == NULL) {
    	destroy_list(&magazine_head);
        return;
    }

    note_head->word = NULL;
    note_head->num_of_words = 0;
    note_head->next = NULL;

    for(int i = 0; i < note_count; ++i) {
    	int word_size = 0;
        char *start_of_word = *(note) + idx;
        while (*((*note) + idx) != '\0') {
            ++word_size;
            ++idx;
        }

        append_node(&note_head, start_of_word, word_size);
        ++idx;
    }

    //check if can make note from magazine
    struct Node *tmp_note_node = note_head;
    while (tmp_note_node != NULL) {
        struct Node *tmp_mag_node = magazine_head;
        bool is_legal_word = 0;
        while (tmp_mag_node != NULL) {
            if (strcmp(tmp_note_node->word, tmp_mag_node->word) == 0) {
                if(tmp_note_node->num_of_words > tmp_mag_node->num_of_words) {
                    printf("No");
                    destroy_list(&magazine_head);
                    destroy_list(&note_head);
                    return;
                }

                is_legal_word = 1;
            }

            tmp_mag_node = tmp_mag_node->next;
        }

        if(is_legal_word == 0) {
        	printf("No");
            destroy_list(&magazine_head);
            destroy_list(&note_head);
            return;
        }

        tmp_note_node = tmp_note_node->next;
    }

    printf("Yes");
    destroy_list(&magazine_head);
    destroy_list(&note_head);
}

void append_node(struct Node **head, char *word, int word_size){
    struct Node *tmp = *head;
    char *new_word = (char*)malloc(sizeof(char) * (word_size + 1));
    if (new_word == NULL) {
        printf("Failed to create new_word\n");
        free(new_word);
        return;
    }

    for (int i = 0; i < word_size; ++i) {
        new_word[i] = word[i];
    }
    new_word[word_size] = '\0';

    if(tmp->word != NULL){
    	if (strcmp(new_word, tmp->word) == 0) {
    	    ++(tmp->num_of_words);
    	    free(new_word);
    	    return;
    	}
    	while (tmp->next != NULL) {
    		if (strcmp(new_word, tmp->word) == 0) {
    			++(tmp->num_of_words);
    			free(new_word);
    			return;
    		}

    		tmp = tmp->next;
    	}
    }

    if ((*head)->word == NULL){
        (*head)->word = new_word;
        (*head)->num_of_words = 1;
        (*head)->next = NULL;
        return;
    }

    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Failed to create a node\n");
        free(new_node);
        return;
    }

    new_node->word = new_word;
    new_node->num_of_words = 1;
    new_node->next = NULL;



    tmp->next = new_node;
}

void destroy_list(struct Node **head) {
    struct Node *node = *head;
    while (*head) {
        *head = (*head)->next;
        free(node->word);
        free(node);
        node = *head;
    }
}

void print_list(struct Node *head){
	struct Node *node = head;
    while (node != NULL) {
    	printf("%s\n", node->word);
    	node = node->next;
	}
}


