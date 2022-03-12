#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	char *macroName;
	char *line;
	struct node *next;
}Node;
void insert(Node** pstart,char *name,char *newLine)
{
	Node *ptr;
	char *copyName = malloc(sizeof(name));
	char *copyLine = malloc(sizeof(newLine));
	strcpy(copyName,name);
	strcpy(copyLine,newLine);
	if (*pstart == NULL)
	{
		*pstart = (Node *)malloc(sizeof(Node));
		(*pstart)->macroName = copyName;
    	(*pstart)->line = copyLine;
		(*pstart)->next = NULL;
	}
	else
	{
		ptr = *pstart;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = (Node *)malloc(sizeof(Node));
		ptr = ptr->next;
		ptr->macroName = copyName;
    	ptr->line = copyLine;
		ptr->next = NULL;
	}
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%s - %s\n", head->macroName,head->line);
        head = head->next;
    }
}
char *macroExist(Node *head,char *s)
{
	int counter = 1;
	while (head != NULL)
	{	
		if(head->macroName[0] == s[0] &&head->macroName[1] == s[1])
		{	
			return head->line; 
		}
    counter++;
		head = head->next;
	}
	return NULL;
}
void freeNode(Node *head)
{
	while (head->next != NULL)
		{	
			free(head->line);
			free(head->macroName);
			head = head->next;
		
		}
}
