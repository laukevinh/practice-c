#include <stdio.h>
#include "linkedlist.h"

int main(void)
{
    test_linked_list();
    test_length();
    test_reverse();
    return 0;
}

void test_linked_list(void)
{
    printf("Test linked list\n");
    struct LinkedList * list = new_linked_list(0);
    push(list, 1);
    push(list, 2);
    push(list, 3);
    printf("Before: ");
    print_linked_list(list);
    printf("Pop: %d\n", pop(list));
    printf("After: ");
    print_linked_list(list);
    delete_linked_list(list);
}

void test_length(void)
{
    printf("Test list length\n");
    struct LinkedList * list = new_linked_list(0);
    for (int i=1; i<8; i++)
        push(list, i);
    printf("List: ");
    print_linked_list(list);
    printf("Length: %d\n", length(list));
    delete_linked_list(list);
}

void test_reverse(void)
{
    printf("Test reverse list\n");
    struct LinkedList * list = new_linked_list(0);
    for (int i=1; i<8; i++)
        push(list, i);
    printf("Before: ");
    print_linked_list(list);
    reverse(list);
    printf("After: ");
    print_linked_list(list);
    delete_linked_list(list);
}
