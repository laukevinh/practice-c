#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"

struct Queue * new_queue(struct AdjList * data)
{
    struct Queue * q = malloc(sizeof(struct Queue));
    struct Node * new_node = malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    q->tail = q->head = new_node;
    return q;
}

void delete_queue(struct Queue * q)
{
    struct Node * head = q->head;
    while(head != NULL) {
        struct Node * temp = head;
        head = head->next;
        free(temp);
    }
    free(q);
}

void enqueue(struct Queue * q, struct AdjList * data)
{
    struct Node * new_node = malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    if (q->tail == NULL) {
        q->tail = q->head = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

struct AdjList * dequeue(struct Queue * q)
{
    if (q->head == NULL)
        return NULL;

    struct Node * head = q->head;
    struct AdjList * data = q->head->data;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = q->head;
    free(head);
    return data;
}

void push(struct Queue * q, struct AdjList * data)
{
    struct Node * new_node = malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    if (q->head == NULL) {
        q->tail = q->head = new_node;
    } else {
        new_node->next = q->head;
        q->head = new_node;
    }
}

struct AdjList * pop(struct Queue * q)
{
    if (q->head == NULL)
        return NULL;

    struct Node * head = q->head;
    struct AdjList * data = q->head->data;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = q->head;
    free(head);
    return data;
}

int length(struct Queue * q)
{
    struct Node * node = q->head;
    int count = 0;
    while(node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void print_queue(struct Queue * q)
{
    struct Node * node = q->head;
    while (node != NULL) {
        printf("%p ", node->data);
        node = node->next;
    }
    printf("\n");
}
