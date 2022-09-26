#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 255

typedef struct link_node {
	char node_str[MAX_STR_LEN];
	struct link_node *next;
} node;

int compare_node(struct link_node *n1, struct link_node *n2);
struct link_node *compare_list(struct link_node *list, char str[]);
void add_node(struct link_node	*list, char ID[]);
void display_list(struct link_node *head);
void free_list(node *head);
void cleanInput(char* input);

void add(struct link_node *list, char ID[]) {
	node *newNode;
	if (list == NULL){
		newNode = (node*)malloc(sizeof(node));
		strcpy(newNode->node_str, ID);
		newNode->next = NULL;
		list = newNode;
	}
	else{
		newNode = compare_list(list, ID);
		if (newNode != NULL){
			add_node(newNode, ID);
		}
	}
}

//Apenas listas não vazias
struct link_node *compare_list(struct link_node *list, char str[]){
	node *node = list;
	int comp = 0;
	while (node->next != NULL && comp == 0){
		if (strcmp(node->node_str, str) == 0){
			comp = 1;
		}
	}
	if (comp == 1){
		return NULL;
	}
	else 
		return node;
}

void add_node(struct link_node	*list, char ID[]){
	node *newNode = (node*)malloc(sizeof(node));
	list->next = newNode;
	strcpy(newNode->node_str, ID);
	newNode->next = NULL;
}

void free_list(node *head) {
	node *prev = head;
	node *cur = head;
	while (cur) {
		prev = cur;
		cur = prev->next;
		free(prev);
	}
}

inline int compare_node(struct link_node *n1, struct link_node *n2) {
	return strcmp(n1->node_str, n2->node_str);
}

void display_list(struct link_node *head) {
	while (head != NULL) {
		printf("%s \n", head->node_str);
		head = head->next;
	}
}