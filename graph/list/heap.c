#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct Heap * new_heap(void)
{
    struct Heap * h = malloc(sizeof(struct Heap));
    h->capacity = MIN_CAPACITY;
    h->size = 0;
    h->edges = malloc(sizeof(struct Edge) * h->capacity);
    return h;
}

void delete_heap(struct Heap * h)
{
    if (h != NULL) {
        if (h->edges != NULL)
            free(h->edges);
        free(h);
    }
}

void resize_heap (struct Heap * h, int new_capacity)
{
    if (new_capacity > MIN_CAPACITY) {
        struct Edge * new_array = malloc(sizeof(struct Edge) * new_capacity);
        for (int i=0; i<h->size; i++) {
            new_array[i].v1 = h->edges[i].v1;
            new_array[i].v2 = h->edges[i].v2;
            new_array[i].wt = h->edges[i].wt;
        }
        free(h->edges);
        h->edges = new_array;
        h->capacity = new_capacity;
    }
}

int left_child(int n)
{
    return 2 * n + 1;
}

int right_child(int n)
{
    return 2 * n + 2;
}

int parent(int n)
{
    return (n-1) / 2;
}

void swap(struct Edge * i, struct Edge * j)
{
    struct Edge temp = *i;
    *i = *j;
    *j = temp;
}

void sift_up (struct Heap * h, int i)
{
    int parent_i = parent(i);
    if (parent_i >= 0) {
        if (h->edges[i].wt > h->edges[parent_i].wt) {
            swap(&h->edges[i], &h->edges[parent_i]);
            sift_up(h, parent_i);
        }
    }
}

void insert_heap (struct Heap * h, int v1, int v2, int wt)
{
    if (h->size + 1 > h->capacity)
        resize_heap(h, h->capacity * RESIZE_FACTOR);
    h->size++;
    h->edges[h->size-1].v1 = v1;
    h->edges[h->size-1].v2 = v2;
    h->edges[h->size-1].wt = wt;
    sift_up(h, h->size-1);
}

void sift_down(struct Heap * h, int i)
{
    int right_i = right_child(i);
    int left_i = left_child(i);
    if (right_i < h->size) {
        // if root less than either child, swap with larger
        int larger_i = (h->edges[left_i].wt > h->edges[right_i].wt) ? left_i : right_i;
        if (h->edges[i].wt < h->edges[larger_i].wt) {
            swap(&h->edges[i], &h->edges[larger_i]);
            sift_down(h, larger_i);
        }
    } else if (left_i < h->size) {
        // if root less than left child, swap
        if (h->edges[i].wt < h->edges[left_i].wt) {
            swap(&h->edges[i], &h->edges[left_i]);
            sift_down(h, left_i);
        }
    }
}

struct Edge extract_max (struct Heap * h)
{
    if (h->size > 0) {
        struct Edge max = h->edges[0];
        h->edges[0] = h->edges[h->size-1];
        h->size--;
        if (h->size < h->capacity / DOWNSIZE_THRESHOLD)
            resize_heap(h, h->capacity / RESIZE_FACTOR);
        sift_down(h, 0);
        return max;
    }
    printf("Cannot extract max from empty heap\n");
}

struct Edge get_max(struct Heap * h)
{
    if (h->size > 0)
        return h->edges[0];
    printf("Cannot get max from empty heap\n");
}

/*  We start with the parent of the last node in
    the heap, i.e. the first non-leaf node.
    We choose this because its children are leaves, 
    and therefore max heaps by definition. To
    maintain the max heap property, we use sift_down
    at this node.

    We continue moving towards the heap root, fixing
    the max heap property using sift_down. Sift_down
    works because there is at most one node (the parent)
    that may be causing the max heap violation.
*/


void build_max_heap(struct Heap * h)
{
    for (int i=(h->size-1)/2; i>=0; i--) {
        sift_down(h, i);
    }
}            

/*  same as sift_down, but takes an additional param
    size so heap->size doesn't change during sort.
*/

void sift_down_for_sort(struct Heap * h, int i, int size)
{
    int right_i = right_child(i);
    int left_i = left_child(i);
    if (right_i < size) {
        // if root less than either child, swap with larger
        int larger_i = (h->edges[left_i].wt > h->edges[right_i].wt) ? left_i : right_i;
        if (h->edges[i].wt < h->edges[larger_i].wt) {
            swap(&h->edges[i], &h->edges[larger_i]);
            sift_down_for_sort(h, larger_i, size);
        }
    } else if (left_i < size) {
        // if root less than left child, swap
        if (h->edges[i].wt < h->edges[left_i].wt) {
            swap(&h->edges[i], &h->edges[left_i]);
            sift_down_for_sort(h, left_i, size);
        }
    }
}

void heap_sort(struct Heap * h)
{
    for (int i=h->size-1; i>=0; i--) {
        swap(&h->edges[0], &h->edges[i]);
        sift_down_for_sort(h, 0, i);
    }
}
