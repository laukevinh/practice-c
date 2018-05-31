/* insert value at index, where new item points to 
   original item at index */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert(struct Node* head, int index, int i);
void push(struct Node** head, int data);
int pop(struct Node** head);
void printlist(struct Node* node);

int main(void)
{
    struct Node* head = NULL;

    // setup
    for (int i=0; i<10; i++)
        push(&head, i);
    printlist(head);

    // insert
    insert(head, 2, 0);
    printlist(head);

    // teardown
    //for (int i=0; i<10; i++)
    while (head != NULL) {
        printf("pop %i\n", pop(&head));
    }
    printlist(head);

    return 0;
}

void insert(struct Node* head, int index, int i)
{
    struct Node* prev = NULL;
    //go to index
    for (int j=0; j<index && head->next != NULL; j++, head=head->next)
        prev = head;
    //create node
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = i;
    newnode->next = head;
    //insert
    prev->next = newnode;
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
