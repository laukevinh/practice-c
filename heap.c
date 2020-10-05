#include <stdio.h>
#include <stdlib.h>

/* Uses resizable array as heap. Adds heap specific
    methods. */

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
int pop(struct List *);
int empty(struct List *list);
int *left(Heap *, int *, int *);
int *right(Heap *, int *, int *);
int get_max(Heap *);
Heap *insert(Heap *, int);
Heap *sift_down(Heap *, int *, int *);
int rm(Heap *, int *);
int extract_max(Heap *);
Heap *heapify(Heap *);
Heap *heap_sort(Heap *);

int main(void)
{
    Heap *heap;
    int i;
    int vals[SIZE] = { 8, 16, 10, 14, 7, 9, 5, 3};

    heap = newlist();
    printf("Test empty: %d\n", empty(heap) == 1);
    for (i = 0; i < SIZE; i++) {
        append(heap, vals[i]);
        printf("%d ", at(heap, i));
    }
    printf("\ntest left %d\n", 
        *left(heap, heap->arr, heap->arr+len(heap)-1) == 16);
    printf("test left %d\n", 
        *left(heap, heap->arr+2, heap->arr+len(heap)-1) == 9);
    printf("test right %d\n", 
        right(heap, heap->arr+3, heap->arr+len(heap)-1) == NULL);
    sift_down(heap, heap->arr, heap->arr + len(heap) - 1);
    for (i = 0; i < SIZE; i++)
        printf("%d ", at(heap, i));
    printf("\n");
    for (i = 3; i <= 18; i+=3)
        insert(heap, i);
    for (i = 0; i < len(heap); i++)
        printf("%d ", at(heap, i));
    printf("\nTest max: %d\n", get_max(heap) == 18);
    printf("Test len: %d\n", len(heap) == 14);
    printf("Test empty: %d\n", empty(heap) == 0);
    printf("Remove idx 7: %d\n", rm(heap, heap->arr+7));
    for (i = 0; i < len(heap); i++)
        printf("%d ", at(heap, i));
    printf("\nExtract max\n");
    while (!empty(heap))
        printf("%d ", extract_max(heap));
    printf("\nNew heap\n");
    for (i = SIZE - 1; i >= 0; i--)
        append(heap, vals[i]);
    for (i = 0; i < len(heap); i++)
        printf("%d ", at(heap, i));
    printf("\nHeapify\n");
    heapify(heap);
    for (i = 0; i < len(heap); i++)
        printf("%d ", at(heap, i));
    printf("\nNew heap\n");
    while (!empty(heap))
        extract_max(heap);
    for (i = 0; i < SIZE; i++) {
        append(heap, vals[i]);
        printf("%d ", at(heap, i));
    }
    printf("\nHeap sort\n");
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

void swap(int *i, int *j)
{
    int temp;

    temp = *i;
    *i = *j;
    *j = temp;
}

int empty(struct List *list)
{
    return (len(list) == 0);
}

int *left(Heap *heap, int *node, int *end)
{
    int i, len;

    i = node - heap->arr;
    len = end - heap->arr;
    if (node == NULL || i < 0 || 2*i + 1 >= len)
        return NULL;
    else
        return heap->arr + 2*i + 1;
}

int *right(Heap *heap, int *node, int *end)
{
    int i, len;

    i = node - heap->arr;
    len = end - heap->arr;
    if (node == NULL || i < 0 || 2*i + 2 >= len)
        return NULL;
    else
        return heap->arr + 2*i + 2;
}

int *parent(Heap *heap, int *node)
{
    int i;

    if (node == NULL || (i = node - heap->arr) == 0)
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

Heap *sift_up(Heap *heap, int *node)
{
    int *p;

    if ((p = parent(heap, node)) == NULL)
        return heap;
    else if (*node > *p) {
        swap(node, p);
        return sift_up(heap, p);
    } else
        return heap;
}

Heap *insert(Heap *heap, int val)
{
    append(heap, val);
    return sift_up(heap, heap->arr + len(heap) - 1);
}

/* sift_down: aka max_heapify, fixes single violation of
    max heap property in a subtree's root. */
Heap *sift_down(Heap *heap, int *node, int *end)
{
    int *le, *ri, *child;

    le = left(heap, node, end);
    ri = right(heap, node, end);
    if (ri == NULL)
        child = le;
    else
        child = (*le > *ri) ? le : ri;
    if (child != NULL && *child > *node) {
        swap(child, node);
        return sift_down(heap, child, end);
    }
    return heap;
}

/* rm: removes node at index i */
int rm(Heap *heap, int *node)
{
    int val;

    swap(node, heap->arr + len(heap) - 1);
    val = pop(heap);
    if (!empty(heap))
        sift_down(heap, node, heap->arr + len(heap) - 1);
    return val;
}

int extract_max(Heap *heap)
{
    if (!empty(heap))
        return rm(heap, heap->arr);
    else {
        printf("Error: empty heap\n");
        return -1;
    }
}

/* heapify: aka build_max_heap */
Heap *heapify(Heap *heap)
{
    int i;

    if (empty(heap))
        return heap;
    for (i = (len(heap)-1) / 2; i >= 0; i--)
        sift_down(heap, heap->arr+i, heap->arr+len(heap));
    return heap;
}

Heap *heap_sort(Heap *heap)
{
    int i, leng;

    heapify(heap);
    for (leng = len(heap); leng > 1; leng--) {
        swap(heap->arr, heap->arr + leng - 1);
        sift_down(heap, heap->arr, heap->arr + leng - 2);
    }
    return heap;
}