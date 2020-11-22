#include <stdlib.h>
#include <assert.h>

#define SIZE 8
#define GROW 2
#define SHRINK 4

struct List {
    int *_A;
    int _capacity;
    int _n;
};

struct List *newlist(void);
int len(struct List *);
int at(struct List *, int);
struct List *append(struct List *, int);
struct List *resize(struct List *, int);
int pop(struct List *);
struct List *insert(struct List *, int, int);
int pop_at(struct List *, int);
int remove2(struct List *, int);
int find(struct List *, int);
struct List *remove_all(struct List *, int);

int main(void)
{
    struct List *list;
    
    list = newlist();
    for(int i = 0; i < 16; i++)
        append(list, i);
    assert(at(list, 14) == 14);
    assert(len(list) == 16);
    assert(pop(list) == 15);
    assert(len(list) == 15);
    insert(list, 0, 1);
    insert(list, 0, 2);
    assert(len(list) == 17);
    assert(at(list, len(list) - 1) == 14);
    assert(pop_at(list, 0) == 2);
    assert(pop_at(list, len(list) - 1) == 14);
    assert(len(list) == 15);
    assert(find(list, 14) == -1);
    assert(remove2(list, 14) == -1);
    assert(find(list, 13) == 14);
    assert(remove2(list, 13) == 13);
    assert(len(list) == 14);
    remove_all(list, 1);
    assert(len(list) == 12);
    return 0;
}

struct List *newlist(void) 
{
    struct List *L = (struct List *) malloc(sizeof (struct List));
    L->_A = (int *) malloc(sizeof (int) * SIZE);
    L->_capacity = SIZE;
    L->_n = 0;
    return L;
}

int in_bounds(int idx, int n) 
{
    return idx >= 0 && idx < n;
}

int len(struct List *list)
{
    return list->_n;
}

int at(struct List *L, int idx)
{
    if (!in_bounds(idx, L->_n))
        return -1;
    return *(L->_A + idx);
}

struct List *append(struct List *L, int val)
{
    if (len(L) >= L->_capacity)
        resize(L, GROW * L->_capacity);
    L->_A[L->_n] = val;
    L->_n++;
    return L;
}

struct List *resize(struct List *L, int capacity)
{
    int *A = (int *) malloc(sizeof(int) * capacity);
    for (int i = 0; i < len(L); i++)
        A[i] = at(L, i);
    free(L->_A);
    L->_A = A;
    L->_capacity = capacity;
    return L;
}

int pop(struct List *L)
{
    int val;

    if (len(L) < 1)
        return -1;
    val = at(L, len(L) - 1);
    L->_n--;
    if (len(L) < L->_capacity / SHRINK)
        resize(L, L->_capacity / GROW);
    return val;
}

struct List *insert(struct List *L, int idx, int val)
{
    if (!in_bounds(idx, len(L)))
        return NULL;
    if (len(L) + 1 > L->_capacity) {
        int *A, i;
        
        A = (int *) malloc(sizeof(int) * L->_capacity * GROW);
        for (i=0; i < idx; i++)
            A[i] = at(L, i);
        A[i] = val;
        for ( ; i < len(L); i++)
            A[i+1] = at(L, i);
        free(L->_A);
        L->_A = A;
        L->_n++;
        L->_capacity = L->_capacity * GROW;
    } else {
        int i;
        
        for (i = len(L); i > idx; i--)
            L->_A[i] = L->_A[i-1];
        L->_A[i] = val;
        L->_n++;
    }
    return L;
}

int pop_at(struct List *L, int idx)
{
    int val;

    if (!in_bounds(idx, len(L)))
        return -1;
    val = at(L, idx);
    if (len(L) - 1 < L->_capacity / SHRINK) {
        int *A, i;

        A = (int *) malloc(sizeof(int) * L->_capacity / GROW);
        for (i = 0; i < idx; i++)
            A[i] = at(L, i);
        for ( ; i < len(L) - 1; i++)
            A[i] = at(L, i+1);
        free(L->_A);
        L->_A = A;
        L->_n--;
        L->_capacity = L->_capacity / GROW;
    } else {
        for (int i = idx; i < len(L) - 1; i++)
            L->_A[i] = L->_A[i+1];
        L->_n--;
    }
    return val;
}

int remove2(struct List *L, int val)
{
    int idx;

    if ((idx = find(L, val)) == -1)
        return -1;
    return pop_at(L, idx);
}

int find(struct List *L, int val)
{
    for (int i = 0; i < len(L); i++)
        if (at(L, i) == val)
            return i;
    return -1;
}

struct List *remove_all(struct List *L, int val)
{
    int i, j, *A;

    A = (int *) malloc(sizeof(int) * L->_capacity);
    for (i=0, j=0; i < len(L); i++)
        if (at(L, i) != val)
            A[j++] = at(L, i);
    free(L->_A);
    L->_A = A;
    L->_n = j;
    return L;
}