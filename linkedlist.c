#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct link_node {
	char node_str[MAX_STR_LEN];
	struct link_node *next;
} node;

int compare_node(struct link_node *n1, struct link_node *n2);
struct link_node *add_node(struct link_node	*list, struct link_node *node);
void display_list(struct link_node *head);
void free_list(node *head);
void cleanInput(char* input);

void add(char ID[]) {
	node *head, *newNode;
	head = NULL;
	newNode = (node*)malloc(sizeof(node));
	strcpy(newNode->node_str, input);
	newNode->next = NULL;
	if (input[0] != '\0') {
		head = add_node(head, newNode);
	}
	display_list(head);
}

struct link_node *add_node(struct link_node	*list, struct link_node *node){
   int comp;
	struct link_node *prev, *next;
	if (!list) {
		list = node;
	}
	else {
		prev = NULL;
		next = list;
		while (next && compare_node(node,next)>-1) {
         comp = compare_node(node,next);
			prev = next;
			next = next->next;
		}
      
      if(comp != 0) {
         if (!next) {
            prev->next = node;
         }
         else {
            if (prev) {
               node->next = prev->next;
               prev->next = node;
            }
            else {
               node->next = list;
               list = node;
            }
         }
      }
	}
	return list;
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

int compare_node(struct link_node *n1, struct link_node *n2) {
	return strcmp(n1->node_str, n2->node_str);
}

void display_list(struct link_node *head) {
	while (head) {
		printf("%s \n", head->node_str);
		head = head->next;
	}
}