#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

struct LinkedList * new_linked_list(int data)
{
    struct LinkedList * linkedList = malloc(sizeof(struct LinkedList));
    linkedList->head = malloc(sizeof(struct Node));
    linkedList->head->data = data;
    linkedList->head->next = NULL;
    return linkedList;
}

void delete_linked_list(struct LinkedList * linkedList)
{
    struct Node * head = linkedList->head;
    while(head != NULL) {
        struct Node * temp = head;
        head = head->next;
        free(temp);
    }
    free(linkedList);
}

void push(struct LinkedList * linkedList, int data)
{
    struct Node * new_node = malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = linkedList->head;
    linkedList->head = new_node;
}

int pop(struct LinkedList * linkedList)
{
    struct Node * top = linkedList->head;
    int data = top->data;
    linkedList->head = top->next;
    free(top);
    return data;
}

int length(struct LinkedList * linkedList)
{
    struct Node * node = linkedList->head;
    int count = 0;
    while(node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void reverse(struct LinkedList * linkedList)
{
    struct Node * prev = NULL;
    struct Node * curr = linkedList->head;
    struct Node * next = linkedList->head;
    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    linkedList->head = prev;
}

void print_linked_list(struct LinkedList * linkedList)
{
    struct Node * node = linkedList->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
