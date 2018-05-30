/* value_at(index) */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int value_at(struct Node* head, int i);
void push(struct Node** head, int data);
int pop(struct Node** head);
void printlist(struct Node* node);

int main(void)
{
    struct Node* head = NULL;

    // set up
    for (int i=0; i<100; i+=10)
        push(&head, i);
    printlist(head);

    // value_at(index)
    for (int i=0; i<13; i+=2)
        printf("value_at(%3d) == %3d\n", i, value_at(head, i));

    // teardown
    while (head != NULL) 
        pop(&head);
    printlist(head);

    return 0;
}

int value_at(struct Node* head, int i)
{
    int j;
    for (j=0; j<i && head != NULL; j++)
        head = head->next;
    if (head == NULL) {
        printf("Index Error %i\n", i);
        exit(1);
    } else {
        return head->data;
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
