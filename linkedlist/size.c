/* size */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int size(struct Node* head);
void push(struct Node** head, int data);
void pop(struct Node** head);
void printlist(struct Node* node);

int main(void)
{
    struct Node* head = NULL;

    // set up
    for (int i=0; i<10; i++)
        push(&head, i);
    printlist(head);

    // size
    printf("size: %i\n", size(head));

    // teardown
    while (head != NULL) 
        pop(&head);
    printlist(head);

    return 0;
}

int size(struct Node* head)
{
    int n;
    for (n=0; head != NULL; n++)
        head = head->next;
    return n;
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
void pop(struct Node** head_ref)
{
    struct Node* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    free(temp);
}

void printlist(struct Node* node)
{
    for ( ; node != NULL; node = node->next)
        printf("%i ", node->data);
    printf("\n");
}    
