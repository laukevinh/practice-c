#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"
#define ERR_OUT_OF_BOUNDS -1

struct Heap* new_heap(int count)
{
    if (count <= 0) {
        printf("Err heap count must be > 0\n");
        exit(EXIT_FAILURE);
    }
    struct Heap* heap = malloc(sizeof(struct Heap));
    heap->count = count;
    heap->height = (int) log2(count);
    if (count > HEAP_MIN_CAPACITY) {
        heap->capacity = pow(2, heap->height+1) - 1;
    } else {
        heap->capacity = HEAP_MIN_CAPACITY;
    }
    heap->data = malloc(sizeof(int) * heap->capacity);
    return heap;
}

void delete_heap(struct Heap* heap)
{
    free(heap->data);
    free(heap);
}

void upsize(struct Heap* heap, int count)
{
    struct Heap* newheap = new_heap(count);
    for (int i=0; i<heap->count; i++)
        *(newheap->data+i) = *(heap->data+i);
    free(heap->data);
    heap->data = newheap->data;
    heap->count = newheap->count;
    heap->height = newheap->height;
    heap->capacity = newheap->capacity;
    free(newheap);
}

void downsize(struct Heap* heap, int count)
{
    struct Heap* newheap = new_heap(count);
    for (int i=0; i<newheap->count; i++)
        *(newheap->data+i) = *(heap->data+i);
    free(heap->data);
    heap->data = newheap->data;
    heap->count = newheap->count;
    heap->height = newheap->height;
    heap->capacity = newheap->capacity;
    free(newheap);
}

void resize(struct Heap* heap, int count)
{
    int new_height = (int) log2(count);
    if (new_height < heap->height) {
        downsize(heap, count);
    } else if (new_height > heap->height) {
        upsize(heap, count);
    } else {
        heap->count = count;
    }
}

void check_bounds(struct Heap* heap, int index)
{
    if (index < 0 || index > heap->count)
        exit(ERR_OUT_OF_BOUNDS);
}

int left_val(struct Heap* heap, int index)
{
    check_bounds(heap, index);
    return *(heap->data + 2 * index + 1);
}

int right_val(struct Heap* heap, int index)
{
    check_bounds(heap, index);
    return *(heap->data + 2 * index + 2);
}

int parent_val(struct Heap* heap, int index)
{
    check_bounds(heap, index);
    return *(heap->data + (index-1)/2);
}

int left_ind(int index)
{
    return 2 * index + 1;
}

int right_ind(int index)
{
    return 2 * index + 2;
}

int parent_ind(int index)
{
    return (index-1) / 2;
}

int get_index_lgr_child(struct Heap* heap, int index)
{
    if ( left_val(heap, index) > right_val(heap, index) )
        return left_ind(index);
    return right_ind(index);
}

int depth(int index)
{
    return log2(index + 1.00);
}

void max_heapify(struct Heap* heap)
{
    /* start from index n/2 since all leaves
       are max heaps. fix max heap property
       level by level. first pass moves max
       element to top, so second pass only 
       needs to process up to 2nd level, third
       pass up to 3rd level, etc.
    */
    int last_index, level_index, temp;
    int *arr, *curr, *max;
    last_index = heap->count-1;
    arr = heap->data;
    /* get index of first element in current level
       and update after each pass
    */
    level_index = 0;
    for (int h=heap->height; h>=0; h--) {
        for (int i=parent_ind(last_index); i>=level_index; i--) {
            curr = arr + i;
            max = arr + get_index_lgr_child(heap, i);
            if (*curr < *max) {
                temp = *curr;
                *curr = *max;
                *max = temp;
            }
        }
        level_index = left_ind(level_index);
    }
}

int get_max(struct Heap* heap)
{
    return *(heap->data);
}

int pop_max(struct Heap* heap)
{
    // swap max with last, delete, max_heapify
    int *ptfirst, *ptlast;
    int max;
    ptfirst = heap->data;
    ptlast = ptfirst + heap->count - 1;

    max = *ptfirst;
    *ptfirst = *ptlast;

    resize(heap, heap->count - 1);
    max_heapify(heap);
    return max;
}

void insert(struct Heap* heap, int i)
{
    // increase heap size, add i to end, max heapify
    resize(heap, heap->count + 1);
    int* ptlast = heap->data + heap->count - 1;
    *ptlast = i;
    max_heapify(heap);
}

void print_heap(struct Heap* heap)
{
    printf("Count, Capacity, Height: (%d,%d,%d)\n", 
        heap->count, heap->capacity, heap->height);
    for (int i=0; i<heap->count; i++)
        printf("%d ", *(heap->data + i));
    printf("\n");
}

void print_heap_pyr(struct Heap* heap)
{
    int* data = heap->data;
    int h = heap->height;
    int count_to_next_depth = 1;
    int nodes_this_level = 1;
    printf("%3d|  ", h);
    for (int i=0; i<heap->count; i++) {
        printf("%3d", *(data + i));
        count_to_next_depth--;
        if (count_to_next_depth == 0) {
            printf("\n");
            printf("%3d|  ", --h);
            nodes_this_level *= 2;
            count_to_next_depth = nodes_this_level;
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

void test_heap(void)
{
    struct Heap* heap;
    for (int i=1; i<64; i+=40) {
        heap = new_heap(i);
        print_heap(heap);
        delete_heap(heap);
    }
}

void test_get_children(void)
{
    struct Heap* heap = new_heap(32);
    for (int i=0; i<32; i++)
        *(heap->data + i) = i;
    printf("Node index: %d\n", 4);
    printf("Parent index: %d\n", parent_ind(4));
    printf("LChild index: %d\n", left_ind(4));
    printf("RChild index: %d\n", right_ind(4));
    print_heap(heap);
    delete_heap(heap);
}

void test_max_heapify(void)
{
    printf("Max heapify:\n");
    struct Heap* heap;
    heap = new_heap(7);
    *(heap->data + 0) = 4;
    *(heap->data + 1) = 8;
    *(heap->data + 2) = 13;
    *(heap->data + 3) = 6;
    *(heap->data + 4) = 2;
    *(heap->data + 5) = 7;
    *(heap->data + 6) = 12;
    printf("Before\n");
    print_heap_pyr(heap);
    max_heapify(heap);
    printf("After\n");
    print_heap_pyr(heap);
    delete_heap(heap);
}

void test_pop_max(void)
{
    printf("Pop max and insert:\n");
    struct Heap* heap;
    heap = new_heap(7);
    *(heap->data + 0) = 4;
    *(heap->data + 1) = 8;
    *(heap->data + 2) = 13;
    *(heap->data + 3) = 6;
    *(heap->data + 4) = 2;
    *(heap->data + 5) = 7;
    *(heap->data + 6) = 12;
    max_heapify(heap);
    printf("Before:\n");
    print_heap_pyr(heap);
    printf("Pop max: %d\n", pop_max(heap));
    print_heap_pyr(heap);
    printf("Insert 100\n");
    insert(heap, 100);
    print_heap_pyr(heap);
    
    for (int i=0; i<20; i++)
        insert(heap, i);
    print_heap_pyr(heap);
    delete_heap(heap);
}
