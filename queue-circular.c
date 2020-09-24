#include <stdio.h>
#include <stdlib.h>

/* time complexity of this implementation's
    enqueue is O(1), dequeue is O(1). Once full, it will
    not expand nor overwrite existing elements. */

struct Queue {
    int front;
    int rear;
    int cap;
    int *arr;
};

struct Queue *newqueue(int);
int full(struct Queue *);
int empty(struct Queue *);
int enqueue(struct Queue *, int);
int dequeue(struct Queue *);

int main(void)
{
    struct Queue *q;
    int i, cap;

    cap = 16;
    q = newqueue(cap);
    for (i = 0; i < 10; i++)        /* partially fill queue */
        enqueue(q, i);
    while (!empty(q))
        printf("%d ", dequeue(q));  /* dequeue */
    printf("\n");
    for (i = 0; i < 10; i++)        /* enqueue and wrap around */
        enqueue(q, i);
    while (!empty(q))
        printf("%d ", dequeue(q));  /* dequeue */
    printf("\n");
    for (i = 0; i < cap - 1; i++)   /* cap is 1 less than actual */
        enqueue(q, i);              /* array size cuz full is */
    while (!empty(q))               /* when rear == front - 1. */
        printf("%d ", dequeue(q));  /* Filling actual array */
    printf("\n");                   /* requires rear == front which*/
    return 0;                       /* clashes with def of empty. */
}

struct Queue *newqueue(int cap)
{
    struct Queue *q;

    q = (struct Queue *) malloc(sizeof(struct Queue));
    q->front = q->rear = 0;
    q->cap = cap;
    q->arr = (int *) malloc(sizeof(int) * cap);
}

int full(struct Queue *q)
{
    return q->rear == q->front - 1;
}

int empty(struct Queue *q)
{
    return q->rear == q->front;
}

int enqueue(struct Queue *q, int i)
{
    if (full(q)) {
        printf("Error: full queue\n");
        return -1;
    }
    q->arr[q->rear] = i;
    q->rear = (q->rear + 1) % q->cap;
    return 0;
}

int dequeue(struct Queue *q)
{
    int i;

    if (empty(q)) {
        printf("Error: empty queue\n");
        return -1;
    }
    i = q->arr[q->front];
    q->front = (q->front + 1) % q->cap;
    return i;
}