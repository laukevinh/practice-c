#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#define TRUE 1
#define FALSE 0

struct Node* new_node(int data)
{
    struct Node* node = malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

struct LinkedList * new_list(void)
{
    struct LinkedList * list = malloc(sizeof(struct LinkedList));
    list->head = NULL;
    return list;
}

void delete_list(struct LinkedList * list)
{
    struct Node * head = list->head;
    while(head != NULL) {
        struct Node * temp = head->next;
        free(head);
        head = temp;
    }
    free(list);
}

int length(struct LinkedList * list)
{
    struct Node * node = list->head;
    int count = 0;
    while(node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

int empty(struct LinkedList * list)
{
    return (list->head == NULL) ? TRUE : FALSE;
}

struct Node* node_at(struct LinkedList * list, int index)
{
    struct Node* node = list->head;
    for (int i=0; i<index; i++) {
        if (node == NULL)
            break;
        node = node->next;
    }
    return node;
}
    

void push_front(struct LinkedList * list, int data)
{
    struct Node * node = new_node(data);
    node->next = list->head;
    list->head = node;
}

int pop_front(struct LinkedList * list)
{
    if (list->head == NULL) {
        printf("Cannot pop empty list\n");
        exit(EXIT_FAILURE);
    }
    struct Node * node = list->head;
    list->head = list->head->next;
    int data = node->data;
    free(node);
    return data;
}

void push_back(struct LinkedList * list, int data)
{
    struct Node* head = list->head;
    if (!empty(list)) {
        while (head->next != NULL)
            head = head->next;
        head->next = new_node(data);
    }
}

int pop_back(struct LinkedList * list)
{
    if (list->head == NULL) {
        printf("Cannot pop empty list\n");
        exit(EXIT_FAILURE);
    }
    struct Node* prev = NULL;
    struct Node* node = list->head;
    while (node->next != NULL) {
        prev = node;
        node = node->next;
    }
    int data = node->data;
    free(node);
    if (prev != NULL)
        prev->next = NULL;
    else
        list->head = NULL;
    return data;
}

int front(struct LinkedList * list)
{
    if (list->head == NULL) {
        printf("Cannot access empty list\n");
        exit(EXIT_FAILURE);
    }
    return list->head->data;
}
    
int back(struct LinkedList * list)
{
    if (list->head == NULL) {
        printf("Cannot access empty list\n");
        exit(EXIT_FAILURE);
    }
    struct Node* node = list->head;
    while (node->next != NULL)
        node = node->next;
    return node->data;
}

void insert(struct LinkedList * list, int index, int data)
{
    if (list->head == NULL) {
        printf("Cannot insert into empty list\n");
        exit(EXIT_FAILURE);
    }
    struct Node* prev = NULL;
    struct Node* node = list->head;
    int count = 0;
    while (count < index && node != NULL) {
        count++;
        prev = node;
        node = node->next;
    }
    if (count < index) {
        printf("Index %d out of bounds\n", index);
        exit(EXIT_FAILURE);
    }
    struct Node* new = new_node(data);
    new->next = node;
    if (prev != NULL)
        prev->next = new;
    else
        list->head = new;
}
    
void erase(struct LinkedList * list, int index)
{
    if (list->head == NULL) {
        printf("Nothing to erase in empty list\n");
        exit(EXIT_FAILURE);
    }
    struct Node* prev = NULL;
    struct Node* node = list->head;
    int count = 0;
    while (count < index && node != NULL) {
        count++;
        prev = node;
        node = node->next;
    }
    if (count < index) {
        printf("Index %d out of bounds\n", index);
        exit(EXIT_FAILURE);
    }
    if (prev != NULL)
        prev->next = node->next;
    else
        list->head = node->next;
    free(node);
}

int value_n_from_end(struct LinkedList * list, int n)
{
    int len = length(list);
    if (n > len) {
        printf("Index %d out of bounds\n", n);
        exit(EXIT_FAILURE);
    }
    return node_at(list, len - n - 1)->data;
}
    
void reverse(struct LinkedList * list)
{
    struct Node * prev = NULL;
    struct Node * curr = list->head;
    struct Node * next = list->head;
    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

void remove_value(struct LinkedList * list, int data)
{
    if (list->head == NULL) {
        printf("Nothing to remove from empty list\n");
        exit(EXIT_FAILURE);
    }
    struct Node* prev = NULL;
    struct Node* node = list->head;
    while (node != NULL && node->data != data) {
        prev = node;
        node = node->next;
    }
    if (node == NULL) {
        printf("Value %d not found\n", data);
    } else {
        if (prev != NULL)
            prev->next = node->next;
        else
            list->head = node->next;
        free(node);
    }
}
    

void print_list(struct LinkedList * list)
{
    struct Node * node = list->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
