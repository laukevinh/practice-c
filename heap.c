#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define GROW 2
#define SHRINK 4

struct List {
    int cap;
    int len;
    int *arr;
};
typedef struct List Heap;

struct List *newlist(void);
int at(struct List *, int);
struct List *append(struct List *, int);
void *resize(struct List *, int);
int len(struct List *);
int remaining(struct List *);
int pop(struct List *);
/* void insert(struct List *, int, int); */
void delete(struct List *, int);
/* void rm(struct List *, int); */
int find(struct List *, int);
int empty(struct List *list);
/* void prepend(struct List *, int); */
int *left(Heap *, int);
int *right(Heap *, int);
int get_max(Heap *);
void insert(Heap *, int);
int rm(Heap *, int);
int extract_max(Heap *);
int sift_down(Heap *, int);
Heap *heapify(Heap *);
Heap *heap_sort(Heap *);

int main(void)
{
    int i;
    Heap *heap;

    heap = newlist();
    printf("Empty: %d\n", empty(heap));
    append(heap, 8);
    append(heap, 16);
    append(heap, 10);
    append(heap, 14);
    append(heap, 7);
    append(heap, 9);
    for (i = 0; i < 6; i++)
        printf("%d ", at(heap, i));
    printf("\n");
    printf("left(%d): %2d\n", 0, *left(heap, 0));
    printf("left(%d): %2d\n", 2, *left(heap, 2));
    printf("right(%d): NULL %d\n", 2, (right(heap, 2) == NULL));
    sift_down(heap, 0);
    for (i = 0; i < 6; i++)
        printf("%d ", at(heap, i));
    printf("\n");
    for (i = 3; i < 21; i+=3)
        insert(heap, i);
    for (i = 0; i < len(heap); i++)
        printf("%d ", at(heap, i));
    printf("\nMax: %2d\n", get_max(heap));
    printf("Size/Len: %2d\n", len(heap));
    printf("Empty: %d\n", empty(heap));
    printf("Remove idx 3: %2d\n", rm(heap, 3));
    while (!empty(heap))
        printf("%d ", extract_max(heap));
    printf("\nSize/Len: %2d\n", len(heap));
    for (i = 0; i < 13; i++)
        append(heap, i * i);
    heapify(heap);
    for (i = 0; i < 13; i++)
        printf("%d ", at(heap, i));
    printf("\n");
    while (!empty(heap))
        extract_max(heap);
    append(heap, 13);
    append(heap, 23);
    append(heap, 7);
    append(heap, 80);
    append(heap, 2);
    append(heap, 3);
    append(heap, 10);
    append(heap, 100);
    append(heap, 100);
    heap_sort(heap);
    for (i = 0; i < len(heap); i++)
        printf("%d ", at(heap, i));
    printf("\n");
    return 0;
}

/* newlist: creates new list */
struct List *newlist(void)
{
    struct List *list;
    
    list = (struct List *) malloc(sizeof(struct List));
    list->cap = SIZE;
    list->len = 0;
    list->arr = (int *) malloc(sizeof(int) * SIZE);
    return list;
}

/* at:  returns value at index i */
int at(struct List *list, int i)
{
    if (i > list->len - 1 || i < 0) {
        printf("Error: Index %d out of bounds\n", i);
        return -1;
    }
    return list->arr[i];
}

/* append:  adds new element to end of list */
struct List *append(struct List *list, int i)
{
    if (list == NULL)
        list = newlist();
    if (list->len + 1 > list->cap)
        resize(list, list->cap * GROW);
    list->arr[list->len++] = i;
    return list;
}

/* resize:  copies contents of array to new array of size n */
void *resize(struct List *list, int n)
{
    int *arr, i;

    arr = (int *) malloc(sizeof(int) * n);
    for (i = 0; i < list->len; i++)
        arr[i] = list->arr[i];
    free(list->arr);
    list->arr = arr;
    list->cap = n;
}

/* len:     shows length of array used */
int len(struct List *list)
{
    return list->len;
}

/* remaining:   shows empty slots remaining in capacity */
int remaining(struct List *list)
{
    return list->cap - list->len;
}

/* pop:     removes last item in array */
int pop(struct List *list)
{
    int i;

    i = list->arr[list->len - 1];
    list->len--;
    if (list->len * SHRINK <= list->cap 
            && list->cap / GROW >= SIZE)
        resize(list, list->cap / GROW);
    return i;
}

/* insert:  inserts item at index, shifts that index's 
    value and trailing elements to the right */
/* void insert(struct List *list, int idx, int i)
{
    int j;
    void swap(int *, int *);

    if (idx < 0 || idx > list->len - 1)
        printf("Error: Index %d out of bounds\n", idx);
    else
        for (j = idx; j < list->len; j++)
            swap(&i, list->arr + j);
        append(list, i);
} */

void swap(int *i, int *j)
{
    int temp;

    temp = *i;
    *i = *j;
    *j = temp;
}

/* delete:  delete item at index, shifts all trailing 
    elements left */
void delete(struct List *list, int idx)
{
    int i;
    void swap(int *, int *);

    if (idx < 0 || idx > list->len - 1)
        printf("Error: Index %d out of bounds\n", idx);
    else
        for (i = idx; i < list->len - 1; i++)
            swap(list->arr + i, list->arr + i + 1);
        pop(list);
}

/* rm:  looks for value and removes index holding 
    it (even if in multiple places) */
/* void rm(struct List *list, int i)
{
    int idx;
    void delete(struct List *, int);

    for (idx = list->len-1; idx >= 0; idx--)
        if (at(list, idx) == i)
            delete(list, idx);
} */

/* find:    looks for value and returns first index
    with that value, -1 if not found */
int find(struct List *list, int i)
{
    int idx, len(struct List *);

    for (idx = 0; idx < len(list); idx++)
        if (at(list, idx) == i)
            return idx;
    return -1;
}

int empty(struct List *list)
{
    return (len(list) == 0);
}

/* prepend: inserts at index 0 */
/* void prepend(struct List *list, int i)
{
    if (empty(list))
        append(list, i);
    else
        insert(list, 0, i);
} */

int *left(Heap *heap, int i)
{
    return (i<0 || 2*i+1 >= len(heap)) ? NULL : heap->arr+(2*i+1);
}

int *right(Heap *heap, int i)
{
    return (i<0 || 2*i+2 >= len(heap)) ? NULL : heap->arr+(2*i+2);
}

int *parent(Heap *heap, int *ip)
{
    int i;

    i = ip - heap->arr;
    if (i == 0)
        return NULL;
    else if (i % 2 == 0)
        return heap->arr + (i - 1) / 2;
    else
        return heap->arr + i / 2;
}

int get_max(Heap *heap)
{
    return at(heap, 0);
}

void sift_up(Heap *heap, int *ip)
{
    if (ip == NULL || ip == heap->arr)
        ;
    else if (*ip > *parent(heap, ip)) {
        swap(ip, parent(heap, ip));
        sift_up(heap, parent(heap, ip));
    }
}

void insert(Heap *heap, int i)
{
    append(heap, i);
    sift_up(heap, heap->arr + len(heap) - 1);
}

/* sift_down: aka max_heapify, fixes single violation of
    max heap property in a subtree's root. */
int sift_down(Heap *heap, int i)
{
    int *le, *ri, *node, *child;

    if (i < 0 || i >= len(heap)) {
        printf("Error: Index out of bounds\n");
        return -1;
    }
    node = heap->arr+i;
    le = left(heap, i);
    ri = right(heap, i);
    if (ri == NULL)
        child = le;
    else
        child = (*le > *ri) ? le : ri;
    if (child != NULL && *node < *child) {
        swap(node, child);
        sift_down(heap, child - heap->arr);
    }
}

/* rm: removes node at index i */
int rm(Heap *heap, int idx)
{
    int val;

    swap(heap->arr + idx, heap->arr + len(heap) - 1);
    val = pop(heap);
    if (!empty(heap))
        sift_down(heap, idx);
    return val;
}

int extract_max(Heap *heap)
{
    /* int max;

    swap(heap->arr, heap->arr + len(heap) - 1);
    max = pop(heap);
    if (!empty(heap))
        sift_down(heap, 0);
    return max; */
    return rm(heap, 0);
}

/* heapify: aka build_max_heap */
Heap *heapify(Heap *heap)
{
    int i;

    for (i = (len(heap)-1) / 2; i >= 0; i--)
        sift_down(heap, i);
    return heap;
}

int *left2(Heap *heap, int i, int end)
{
    return (i<0 || 2*i+1 >= end) ? NULL : heap->arr+(2*i+1);
}

int *right2(Heap *heap, int i, int end)
{
    return (i<0 || 2*i+2 >= end) ? NULL : heap->arr+(2*i+2);
}

/* sift_down_2: aka max_heapify, fixes single violation of
    max heap property in a subtree's root. overrides normal
    length and stops at end */
int sift_down_2(Heap *heap, int i, int end)
{
    int *le, *ri, *node, *child;

    if (i < 0 || i >= end) {
        printf("Error: Index out of bounds\n");
        return -1;
    }
    node = heap->arr+i;
    le = left2(heap, i, end);
    ri = right2(heap, i, end);
    if (ri == NULL)
        child = le;
    else
        child = (*le > *ri) ? le : ri;
    if (child != NULL && *node < *child) {
        swap(node, child);
        sift_down_2(heap, child - heap->arr, end);
    }
}

Heap *heap_sort(Heap *heap)
{
    int end;

    heapify(heap);
    end = len(heap);
    while (end > 0) {
        swap(heap->arr, heap->arr + end - 1);
        --end;
        if (end > 0)
            sift_down_2(heap, 0, end);
    }
    return heap;
}