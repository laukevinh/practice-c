/* pop removes front item and returns value */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head, int data);
int pop_back(struct Node* head);
void printlist(struct Node* node);

int main(void)
{
    struct Node* head = NULL;

    for (int i=0; i<10; i++)
        push(&head, i);
    printlist(head);

    for (int i=0; i<3; i++)
        printf("pop %i\n", pop_back(head));
    printlist(head);

    return 0;
}

/* Uses reference to head of a list (pointer to pointer) to
   insert new node in front. */
void push(struct Node** head_ref, int data)
{
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->next = *head_ref;
    *head_ref = newnode;
}

/* Go through entire list to remove end node and return
   value. */
int pop_back(struct Node* head)
{
    if (head == NULL) {
        printf("Index Error\n");
        exit(1);
    }
    
    struct Node* prev = NULL;
    while (head->next != NULL) {
        prev = head;
        head = head->next;
    }
    int i = head->data;
    prev->next = NULL; 
    free(head);
    return i;
}

void printlist(struct Node* node)
{
    for ( ; node != NULL; node = node->next)
        printf("%i ", node->data);
    printf("\n");
}    
