/* append aka push end */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void append(struct Node* head, int i);
void printlist(struct Node* head);

int main(void)
{
    struct Node node = {0, NULL};
    struct Node* head = &node;
    struct Node* temp = NULL;

    append(head, 1);
    append(head, 2);
    
    printlist(head);
    
    // teardown 
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(head);
    }

    return 0;
}

/* Go through entire list to add new node at end. */
void append(struct Node* head, int i)
{
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = i;
    newnode->next = NULL;
    while (head->next != NULL)
        head = head->next;
    head->next = newnode;
}

void printlist(struct Node* head)
{
    while (head != NULL) {
        printf("%i ", head->data);
        head = head->next;
    }
}    
