/* push */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head, int i);
void printlist(struct Node* head);

int main(void)
{
    struct Node* head = NULL;

    push(&head, 1);
    printlist(head);
    free(head);

    return 0;
}

/* Uses reference to head of a list (pointer to pointer) to 
   insert new node in front. */
void push(struct Node** head_ref, int i)
{
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = i;
    newnode->next = *head_ref;
    *head_ref = newnode;
}

void printlist(struct Node* head)
{
    while (head != NULL) {
        printf("%i ", head->data);
        head = head->next;
    }
}    
