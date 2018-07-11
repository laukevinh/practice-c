#include <stdio.h>
#include "queue.h"

int main(void)
{
    test_queue();
    test_length();
    return 0;
}

void test_queue(void)
{
    printf("Test queue\n");
    struct Queue * q = new_queue(0);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    printf("Before: ");
    print_queue(q);
    printf("Dequeue: %d\n", dequeue(q));
    printf("After: ");
    print_queue(q);
    delete_queue(q);
}

void test_length(void)
{
    printf("Test list length\n");
    struct Queue * q = new_queue(0);
    for (int i=1; i<8; i++)
        enqueue(q, i);
    printf("Queue: ");
    print_queue(q);
    printf("Length: %d\n", length(q));
    delete_queue(q);
}
