#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#define EXIT_FAILURE 1

struct IntArray* new_array(int len)
{
    struct IntArray* intArray = malloc(sizeof(struct IntArray*));
    intArray->data = malloc(sizeof(int) * len);
    intArray->len= len;
    return intArray;
}

void delete_array(struct IntArray* intArray)
{
    free(intArray->data);
    free(intArray);
}

void resize(struct IntArray* intArray, int new_len)
{
    // make new int array
    int* newData = malloc(sizeof(int) * new_len);
    // copy old to new, careful not to overcopy in downsize
    int min = new_len < intArray->len ? new_len : intArray->len;
    for (int i=0; i<min; i++)
        *(newData + i) = *(intArray->data + i);
    // delete old int array and update array
    free(intArray->data);
    intArray->data = newData;
    intArray->len = new_len;
}

void append(struct IntArray* intArray, int i)
{
    // increase array length by 1 and set to i
    resize(intArray, intArray->len + 1);
    int len = intArray->len - 1;
    *(intArray->data + len) = i;
}

void pop(struct IntArray* intArray)
{
    // reduce size of array
    resize(intArray, intArray->len - 1);
}

void insert(struct IntArray* intArray, int i, int pos)
{
    // make larger array
    int* newData = malloc(sizeof(int) * (intArray->len+1));
    // copy to pos, insert, copy rest
    for (int i=0; i<pos; i++)
        *(newData + i) = *(intArray->data + i);
    *(newData + pos) = i;
    for (int i=pos; i<intArray->len; i++)
        *(newData + i + 1) = *(intArray->data + i);
    // delete old int array and update array
    free(intArray->data);
    intArray->data = newData;
    ++intArray->len;
}

void push(struct IntArray* intArray, int i)
{
    insert(intArray, i, 0);
}

void delete(struct IntArray* intArray, int pos)
{
    // make smaller array
    int new_len = intArray->len-1;
    int* newData = malloc(sizeof(int) * new_len);
    // copy to pos, skip, copy rest
    for (int i=0; i<pos; i++)
        *(newData + i) = *(intArray->data + i);
    for (int i=pos; i<intArray->len-1; i++)
        *(newData + i) = *(intArray->data + i + 1);
    // delete old int array and update array
    free(intArray->data);
    intArray->data = newData;
    --intArray->len;
}

void pop_front(struct IntArray* intArray)
{
    delete(intArray, 0);
}

void update(struct IntArray* intArray, int i, int pos)
{
    if (pos < 0 || pos > intArray->len)
        exit(EXIT_FAILURE);
    *(intArray->data + pos) = i;
}

int find(struct IntArray* intArray, int x)
{
    // go through array, compare one by one
    for (int i=0; i<intArray->len; i++)
        if ( *(intArray->data + i) == x )
            return i;
    return -1;
}

int front(struct IntArray* intArray)
{
    return *intArray->data;
}

int last(struct IntArray* intArray)
{
    return *(intArray->data + intArray->len - 1);
}

void print_array(struct IntArray* intArray)
{
    for (int i=0; i<intArray->len; i++)
        printf("%d ", *(intArray->data+i));
    printf("Length: %d\n", intArray->len);
}
void test_resize(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest resize\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    for (int i=20; i>0; i=i-15) {
        printf("Resizing to %d\n", i);
        resize(intArray, i);
        print_array(intArray);
    }
    delete_array(intArray);
}
void test_append(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest append\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    append(intArray, 100);
    print_array(intArray);
}
void test_push(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest push\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    push(intArray, 100);
    print_array(intArray);
}
void test_pop(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest pop\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    pop(intArray);
    print_array(intArray);
}
void test_pop_front(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest pop front\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    pop_front(intArray);
    print_array(intArray);
}
void test_insert(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest insert\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    insert(intArray, 100, 4);
    print_array(intArray);
}
void test_delete(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest delete\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    delete(intArray, 4);
    print_array(intArray);
}
void test_update(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest update\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    update(intArray, 100, 4);
    print_array(intArray);
}
void test_find(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest find\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = i;
    print_array(intArray);
    int j = 5;
    int k = find(intArray, j);
    printf("Found %i at index %i\n", j, k);
}
void test_front(void)
{
    int len = 10;
    struct IntArray* intArray = new_array(len);
    printf("\nTest front\n");
    for (int i=0; i<intArray->len; i++)
        *(intArray->data+i) = intArray->len - i;
    print_array(intArray);
    printf("front, last: %d %d\n", front(intArray), last(intArray));
}
