#include <stdio.h>
#include <assert.h>
#include "linkedlist.h"

int main(void)
{
    test_list();
    return 0;
}

void test_list(void)
{
    printf("Test linked list\n");
    struct LinkedList * list = new_list();
    for (int i=0; i<3; i++)
        push_front(list, i);
    assert(list->head->data == 2);
    assert(list->head->next->data == 1);
    assert(list->head->next->next->next == NULL);

    //  2 1 0
    printf("Test list length\n");
    assert(length(list) == 3);

    printf("Test node at\n");
    assert(node_at(list, 2) == list->head->next->next);
    assert(node_at(list, 1)->data == 1);
    assert(node_at(list, 3) == NULL);

    //  2 1 0
    printf("Test pop front\n");
    assert(pop_front(list) == 2);
    assert(length(list) == 2);

    //  1 0
    printf("Test push back\n");
    for (int i=4; i<7; i++)
        push_back(list, i);
    assert(list->head->next->next->next->data == 5);
    assert(length(list) == 5);

    //  1 0 4 5 6
    printf("Test pop back\n");
    assert(pop_back(list) == 6);
    assert(length(list) == 4);
    for (int i=0; i<4; i++)
        pop_back(list);

    //  empty list
    printf("Test front\n");
    for (int i=0; i<5; i++)
        push_front(list, i);
    assert(front(list) == 4);
    printf("Test front\n");
    assert(back(list) == 0);

    //  4 3 2 1 0
    printf("Test insert\n");
    insert(list, 2, 8);
    assert(list->head->next->data == 3);
    assert(list->head->next->next->data == 8);
    assert(list->head->next->next->next->data == 2);

    //  4 3 8 2 1 0
    printf("Test erase\n");
    erase(list, 3);
    assert(list->head->next->next->next->data == 1);
    erase(list, 3);
    erase(list, 3);
    assert(list->head->next->next->next == NULL);

    //  4 3 8
    printf("Test value n from end\n");
    assert(value_n_from_end(list, 0) == 8);
    assert(value_n_from_end(list, 2) == 4);

    //  4 3 8
    printf("Test reverse\n");
    reverse(list);
    assert(list->head->data == 8);
    assert(list->head->next->data == 3);
    assert(list->head->next->next->next == NULL);
    
    //  8 3 4
    printf("Test remove value\n");
    remove_value(list, 5);
    remove_value(list, 3);
    assert(list->head->next->data == 4);
    remove_value(list, 4);
    assert(list->head->data == 8);
    remove_value(list, 8);

    delete_list(list);
}
