#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#define EXIT_FAILURE 1

struct IntArray* new_array(void)
{
    struct IntArray* intArray = malloc(sizeof(struct IntArray));
    intArray->len = 0;
    intArray->capacity = MIN_CAPACITY;
    intArray->data = malloc(sizeof(int) * MIN_CAPACITY);
    return intArray;
}

void delete_array(struct IntArray* intArray)
{
    free(intArray->data);
    free(intArray);
}

/*  Resize

    Make a new array. Copy old to new, replace with new data.
*/

void resize(struct IntArray* intArray, int new_capacity)
{
    if (new_capacity >= MIN_CAPACITY) {

        int* newData = malloc(sizeof(int) * new_capacity);

        for (int i=0; i<intArray->len; i++)
            *(newData + i) = *(intArray->data + i);

        free(intArray->data);
        intArray->data = newData;
        intArray->capacity = new_capacity;
    }
}

void append(struct IntArray* intArray, int i)
{
    if (intArray->len + 1 > intArray->capacity)
        resize(intArray, intArray->capacity * RESIZE_FACTOR);
    intArray->len++;
    *(intArray->data + intArray->len - 1) = i;
}

int pop(struct IntArray* arr)
{
    if (arr->len <= 0)
        exit(EXIT_FAILURE);
    int i = *(arr->data + arr->len - 1);
    arr->len = arr->len - 1;
    if (arr->len < arr->capacity / DOWNSIZE_THRESHOLD)
        resize(arr, arr->capacity / RESIZE_FACTOR);
    return i;
}

void insert(struct IntArray* arr, int i, int pos)
{
    if (arr->len + 1 > arr->capacity)
        resize(arr, arr->capacity * RESIZE_FACTOR);
    arr->len++;

    for (int i=arr->len; i>pos; i--)
        *(arr->data + i) = *(arr->data + i - 1);
    *(arr->data + pos) = i;
}

void push(struct IntArray* arr, int i)
{
    insert(arr, i, 0);
}

int del(struct IntArray* arr, int pos)
{
    if (arr->len <= 0)
        exit(EXIT_FAILURE);

    if (arr->len - 1 < arr->capacity / DOWNSIZE_THRESHOLD)
        if (arr->capacity / RESIZE_FACTOR > MIN_CAPACITY)
            resize(arr, arr->capacity / RESIZE_FACTOR);

    int result = *(arr->data + pos);
    for (int i=pos; i<arr->len-1; i++)
        *(arr->data + i) = *(arr->data + i + 1);
    arr->len--;
    return result;
}

int pop_front(struct IntArray* arr)
{
    return del(arr, 0);
}

void update(struct IntArray* arr, int i, int pos)
{
    if (pos < 0 || pos > arr->len - 1)
        exit(EXIT_FAILURE);
    *(arr->data + pos) = i;
}

int find(struct IntArray* arr, int x)
{
    // go through array, compare one by one
    for (int i=0; i<arr->len; i++)
        if ( *(arr->data + i) == x )
            return i;
    return -1;
}

int front(struct IntArray* arr)
{
    return *arr->data;
}

int last(struct IntArray* arr)
{
    return *(arr->data + arr->len - 1);
}

void print_array(struct IntArray* arr)
{
    for (int i=0; i<arr->len; i++)
        printf("%d ", *(arr->data+i));
}
