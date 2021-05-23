#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define CAPACITY 8
#define GROW 2
#define SHRINK 4

struct List {
    int _capacity;
    int _size;
    char **_A;
};

struct List *new_list(void);
int len(struct List *);
char *at(struct List *, int);
char *set(struct List *, char *, int);
struct List *append(struct List *, char *);
// struct List *resize(struct List *, int);
// int pop(struct List *);
// struct List *insert(struct List *, int, int);
// int pop_at(struct List *, int);
// int remove2(struct List *, int);
// int find(struct List *, int);
// struct List *remove_all(struct List *, int);
int strcmp(char *, char*);

int main(void)
{
    struct List *L = new_list();

    // test len
    assert(len(L) == 0);
    // test set
    assert(set(L, "Hello", 0) == NULL);
    // test append
    append(L, "Hello");
    assert(strcmp(at(L, 0), "Hello"));
    assert(len(L) == 1);
    // test resize

    for(int i = 0; i < 16; i++)
        append(L, "Hello");
    append(L, "World");
    // for (int i=0; i<len(L); i++)
    //     printf("%3d %s\n", i, at(L, i));
    assert(strcmp(at(L, len(L) - 1), "World"));
    // assert(at(list, 14) == 14);
    // assert(len(list) == 16);
    // assert(pop(list) == 15);
    // assert(len(list) == 15);
    // insert(list, 0, 1);
    // insert(list, 0, 2);
    // assert(len(list) == 17);
    // assert(at(list, len(list) - 1) == 14);
    // assert(pop_at(list, 0) == 2);
    // assert(pop_at(list, len(list) - 1) == 14);
    // assert(len(list) == 15);
    // assert(find(list, 14) == -1);
    // assert(remove2(list, 14) == -1);
    // assert(find(list, 13) == 14);
    // assert(remove2(list, 13) == 13);
    // assert(len(list) == 14);
    // remove_all(list, 1);
    // assert(len(list) == 12);
    return 0;
}

struct List *new_list(void) {
    struct List *L = (struct List *) malloc(sizeof(struct List));
    L->_capacity = CAPACITY;
    L->_size = 0;
    L->_A = (char **) malloc(sizeof(char *) * L->_capacity);
    return L;
}

int len(struct List *L) {
    return L->_size;
}

int position(struct List *L, int i) {
    int pos = i;
    if (pos < 0) {
        pos += len(L);
    }
    if (pos < 0 || len(L) <= pos) {
        return -1;
    } else {
        return pos;
    }
}

char *at(struct List *L, int i) {
    int pos = position(L, i);
    if (pos < 0) {
        return NULL;
    } else {
        return L->_A[pos];
    }
}

char *set(struct List *L, char *new, int i) {
    int pos = position(L, i);
    if (pos < 0) {
        return NULL;
    } else {
        L->_A[pos] = new;
        return L->_A[pos];
    }
}

char **resize(struct List *L, int size) {
    char **A = (char **) malloc(sizeof(char *) * size);
    for (int i=0; i<len(L); i++) {
        A[i] = L->_A[i];
    }
    return A;
}

struct List *append(struct List *L, char * new) {
    if (L->_capacity <= L->_size) {
        char **old = L->_A;
        L->_A = resize(L, L->_capacity * GROW);
        L->_capacity *= GROW;
        free(old);
    }
    L->_size++;
    set(L, new, len(L) - 1);
    return L;
}

int strcmp(char *s, char *t) {
    for ( ; *s != '\0' && *t != '\0'; *s++, *t++) {
        if (*s != *t)
            return 0;
    }
    return 1;
}