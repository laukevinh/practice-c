/* removes the first item in list with this value */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int remove_value(struct Node** head, int i);
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

    // remove_value
    remove_value(&head, 5);
    remove_value(&head, 9);
    printlist(head);

    // teardown
    while (head != NULL)
        printf("pop %i\n", pop(&head));
    printlist(head);

    return 0;
}

int remove_value(struct Node** head_ref, int i)
{
    struct Node *prev = NULL, *curr = *head_ref;
    if (curr != NULL && curr->data == i) {
        *head_ref = curr->next;
        free(curr);
        return 0;
    }
    while (curr->next != NULL && curr->data != i) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Error item not found\n");
        return -1;
    } else {
        prev->next = curr->next;
        free(curr);
        return 0;
    }
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
