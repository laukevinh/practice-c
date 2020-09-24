#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
};

struct Queue {
    struct Node *head;
    struct Node *tail;
};

struct Queue *newqueue(void);
int enqueue(struct Queue *, int);
int dequeue(struct Queue *);
int empty(struct Queue *);

int main(void)
{
    struct Queue *q;
    int i;

    q = newqueue();
    for (i = 0; i < 10; i++)
        enqueue(q, i);
    for (i = 0; i < 10; i++)
        printf("%d ", dequeue(q));
    printf("\n%s\n", (empty(q)) ? "Empty" : "Not empty");
    return 0;
}

struct Queue *newqueue(void)
{
    struct Queue *q;

    q = (struct Queue *) malloc(sizeof(struct Queue));
    q->head = q->tail = NULL;
    return q;
}

struct Node *newnode(int val)
{
    struct Node *node;

    node = (struct Node *) malloc(sizeof(struct Node));
    node->val = val;
    node->next = NULL;
    return node;
}

int enqueue(struct Queue *q, int val)
{
    struct Node *newnode(int);

    if (q == NULL) {
        printf("Error: Null Queue\n");
        return -1;
    }
    if (q->tail == NULL)
        q->head = q->tail = newnode(val);
    else {
        q->tail->next = newnode(val);
        q->tail = q->tail->next;
    }
    return 0;
}

int dequeue(struct Queue *q)
{
    int i;
    struct Node *node;

    if (q == NULL || q->head == NULL) {
        printf("Error: Null Queue\n");
        return -1;
    }
    i = q->head->val;
    node = q->head->next;
    free(q->head);
    q->head = node;
    if (node == NULL)
        q->tail = q->head;
    return i;
}

int empty(struct Queue *q)
{
    return (q == NULL || q->head == NULL);
}