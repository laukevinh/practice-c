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

struct List *newlist(void);
int at(struct List *, int);
struct List *append(struct List *, int);
void *resize(struct List *, int);
int len(struct List *);
int remaining(struct List *);
int pop(struct List *);
void insert(struct List *, int, int);
void delete(struct List *, int);
void rm(struct List *, int);
int find(struct List *, int);
int empty(struct List *list);
void prepend(struct List *, int);

int main(void)
{
    int i;
    struct List *list;

    list = newlist();
    at(list, 0);        /* show index error */
    for (i = 0; i < SIZE; i++)
        append(list, i);                /* fill the list */
    printf("idx %d: %4d\n", 1, at(list, 1));        /* show 1 */
    append(list, 100);                          /* resize array */
    printf("idx %d: %4d\n", SIZE, at(list, SIZE));     /* 100 */
    printf("len: %d\n", len(list));                 /* show 9 */
    printf("remaining: %d\n", remaining(list));     /* show 7 */
    printf("pop: %d\n", pop(list));             /* show 100 */
    at(list, SIZE);     /* show len was adjusted, index error */
    printf("remaining: %d\n", remaining(list)); /* show 8 */
    while (len(list) > 0)
        printf("%d ", pop(list));       /* empty the list */
    printf("\nremaining: %d\n", remaining(list));   /* show 8 */
    for (i = 0; i < SIZE; i++)
        append(list, i);                /* fill the list */
    insert(list, 2, 200);
    insert(list, 0, 100);
    for (i = 0; i < len(list); i++)
        printf("%d ", at(list, i));     /* show inserts */
    printf("\nremaining: %d\n", remaining(list));   /* show 6 */
    delete(list, 0);
    delete(list, 2);
    for (i = 0; i < len(list); i++)
        printf("%d ", at(list, i));     /* show deletes */
    printf("\n");
    insert(list, 6, 100);
    insert(list, 4, 100);
    insert(list, 2, 100);
    for (i = 0; i < len(list); i++)
        printf("%d ", at(list, i));     /* show inserts */
    printf("\n");
    rm(list, 100);
    for (i = 0; i < len(list); i++)
        printf("%d ", at(list, i));     /* show removals */
    printf("\nfind %d: %d\n", 100, find(list, 100)); /* -1 */
    printf("find %d: %d\n", 6, find(list, 6));  /* 6 */
    prepend(list, 100);
    for (i = 0; i < len(list); i++)
        printf("%d ", at(list, i));     /* show prepend */
    while (len(list) > 0)
        pop(list);                      /* empty the list */
    printf("\n");
    prepend(list, 100);
    for (i = 0; i < len(list); i++)
        printf("%d ", at(list, i));     /* show prepend */
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
void insert(struct List *list, int idx, int i)
{
    int j;
    void swap(int *, int *);

    if (idx < 0 || idx > list->len - 1)
        printf("Error: Index %d out of bounds\n", idx);
    else
        for (j = idx; j < list->len; j++)
            swap(&i, list->arr + j);
        append(list, i);
}

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
void rm(struct List *list, int i)
{
    int idx;
    void delete(struct List *, int);

    for (idx = list->len-1; idx >= 0; idx--)
        if (at(list, idx) == i)
            delete(list, idx);
}

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
void prepend(struct List *list, int i)
{
    if (empty(list))
        append(list, i);
    else
        insert(list, 0, i);
}