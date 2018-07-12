#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"

struct Queue * new_queue(struct AdjList * data)
{
    struct Queue * q = malloc(sizeof(struct Queue));
    q->head = malloc(sizeof(struct Node));
    q->head->data = data;
    q->head->next = NULL;
    q->head->prev = NULL;
    q->tail = q->head;
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
    if (q->head == NULL) {
        new_node->next = NULL;
        new_node->prev = NULL;
        q->head = new_node;
        q->tail = q->head;
    } else {
        new_node->next = q->head;
        new_node->prev = NULL;
        q->head->prev = new_node;
        q->head = new_node;
    }
}

struct AdjList * dequeue(struct Queue * q)
{
    struct Node * tail = q->tail;
    struct AdjList * data = q->tail->data;
    q->tail = q->tail->prev;
    if (q->tail == NULL)
        q->head = NULL;
    else
        q->tail->next = NULL;
    free(tail);
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
