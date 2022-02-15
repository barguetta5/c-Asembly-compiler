#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char *lable;// lable name
    int value; //ic line
    int base;
    int offset;
    int attribut;//1-exernal, 2-entry ,3-code, 4-data
    struct node * next;
} node_t;

void push(node_t *head,char *lable, int value,int base,int offset,int attribut)
 {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->lable = (char*)malloc(30);
    current->next->lable = lable;
    current->next->value = value;
    current->next->base = base;
    current->next->offset = offset;
    current->next->attribut = attribut;
    current->next->next = NULL;
}
void printNode(node_t *head) {
    node_t *current_node = head;
   	while ( current_node != NULL) {
        printf("%s\n%d\n%d\n%d\n%d\n ", current_node->lable,current_node->value
        ,current_node->base,current_node->offset,current_node->attribut);
        current_node = current_node->next;
    }
}