#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"

int main(void)
{
    test_append();
    test_resize();
    test_push();
    test_pop();
    test_pop_front();
    test_insert();
    test_delete();
    test_update();
    test_find();
    test_front();
    return 0;
}

void test_append(void)
{
    printf("Test append\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    assert(intArray->data[0] == 0);
    assert(intArray->data[8] == 8);
    delete_array(intArray);
}
void test_resize(void)
{
    printf("Test append and del resizing\n");
    struct IntArray* intArray = new_array();
    int len = 17;
    for (int i=0; i<len; i++)
        append(intArray, i);
    assert(intArray->capacity == 32);
    assert(intArray->len == 17);
    resize(intArray, 128);
    pop(intArray);
    assert(intArray->capacity == 64);
    assert(intArray->len == 16);
    for (int i=0; i<16; i++)
        pop(intArray);
    assert(intArray->len == 0);
    assert(intArray->capacity == 16);
    delete_array(intArray);
}
void test_push(void)
{
    printf("Test push\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        push(intArray, i);
    assert(intArray->data[0] == 9);
    assert(intArray->data[8] == 1);
    delete_array(intArray);
}
void test_pop(void)
{
    printf("Test pop\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    assert(pop(intArray) == 9);
    delete_array(intArray);
}
void test_pop_front(void)
{
    printf("Test pop front\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    assert(pop_front(intArray) == 0);
    delete_array(intArray);
}
void test_insert(void)
{
    printf("Test insert\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    insert(intArray, 100, 4);
    assert(intArray->data[4] == 100);
    delete_array(intArray);
}
void test_delete(void)
{
    printf("Test delete\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    del(intArray, 4);
    assert(intArray->data[4] != 4);
    delete_array(intArray);
}
void test_update(void)
{
    printf("Test update\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    update(intArray, 100, 4);
    assert(intArray->data[4] == 100);
    delete_array(intArray);
}
void test_find(void)
{
    printf("Test find\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    assert(find(intArray, 4) == 4);
    assert(find(intArray, 10) == -1);
    delete_array(intArray);
}
void test_front(void)
{
    printf("Test front and last\n");
    int len = 10;
    struct IntArray* intArray = new_array();
    for (int i=0; i<len; i++)
        append(intArray, i);
    assert(front(intArray) == 0);
    assert(last(intArray) == 9);
    delete_array(intArray);
}
