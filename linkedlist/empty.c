/* empty */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int empty(struct Node* head);
void push(struct Node** head, int data);
int pop(struct Node** head);
void printlist(struct Node* node);

int main(void)
{
    struct Node* head = NULL;

    // set up
    for (int i=0; i<10; i++)
        push(&head, i);
    printlist(head);

    // teardown
    while (head != NULL) 
        pop(&head);
    printlist(head);

    // empty
    printf("%s\n", empty(head) ? "Empty" : "Not empty");

    return 0;
}

int empty(struct Node* head)
{
    return (head == NULL) ? 1 : 0;
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

/* Uses reference to head of a list (pointer to pointer) to
   delete node in front. */
int pop(struct Node** head_ref)
{
    if (*head_ref == NULL) {
        printf("Index Error\n");
        exit(1);
    }
    struct Node* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    int i = temp->data;
    free(temp);
    return i;
}

void printlist(struct Node* node)
{
    for ( ; node != NULL; node = node->next)
        printf("%i ", node->data);
    printf("\n");
}    
