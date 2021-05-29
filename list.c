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
char *pop(struct List *);
struct List *insert(struct List *, char *, int);
char *pop_at(struct List *, int);
char *remove_string(struct List *, char *);
int find(struct List *, char *);
int remove_all(struct List *, char *);
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
    assert(strcmp(at(L, len(L) - 1), "World"));
    // test pop
    assert(strcmp(pop(L), "World"));
    while(0 < len(L))
        pop(L);
    assert(len(L) == 0);
    assert(L->_capacity == CAPACITY);

    // test insert
    append(L, "again");
    insert(L, "Hello", 0);
    assert(strcmp(at(L, 0), "Hello"));
    assert(strcmp(pop_at(L, 0), "Hello"));
    assert(len(L) == 1);
    
    append(L, ".");
    insert(L, "Hello", 0);
    insert(L, "world", 1);
    assert(find(L, "again") == 2);
    
    assert(remove_string(L, ".") == ".");
    assert(len(L) == 3);
    
    for (int i = 0; i<5; i++) {
        if (i % 2 == 0) {
            append(L, "two");
        } else {
            append(L, "one");
        }
    }
    assert(len(L) == 8);
    assert(remove_all(L, "two") == 3);
    assert(len(L) == 5);
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

struct List *append(struct List *L, char *new) {
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

char *pop(struct List *L) {
    char *e = L->_A[len(L) - 1];
    L->_size--;
    if (L->_size * SHRINK < L->_capacity && CAPACITY < L->_capacity) {
        char **old = L->_A;
        L->_A = resize(L, L->_capacity / GROW);
        L->_capacity /= GROW;
        free(old);
    }
    return e;
}

struct List *insert(struct List *L, char *new, int i) {
    int j, pos;
    char **A, **old;

    A = old = L->_A;
    if ((pos = position(L, i)) < 0)
        return NULL;
    if (L->_capacity <= L->_size) {
        A = (char **) malloc(sizeof(char *) * L->_capacity * GROW);
        for (j=0; j<pos; j++)
            A[j] = old[j];
    }
    L->_size++;
    for (j=len(L)-1; pos<j; j--)
        A[j] = old[j-1];
    A[pos] = new;
    if (A != old) {
        free(old);
        L->_A = A;
    }
    return L;
}

char *pop_at(struct List *L, int i) {
    int j, pos = position(L, i);
    char *s, **old, **A;
    if (pos < 0)
        return NULL;
    s = L->_A[pos];
    old = A = L->_A;
    if ((len(L) - 1) * SHRINK < L->_capacity && CAPACITY < L->_capacity) {
        A = (char **) malloc(sizeof(char *) * L->_capacity / GROW);
        for (j=0; j<pos; j++)
            A[j] = old[j];
    }
    for (j=pos; j<len(L)-1; j++)
        A[j] = old[j+1];
    L->_size--;
    if (A != old) {
        free(old);
        L->_A = A;
    }
    return s;
}

int find(struct List *L, char *s) {
    for (int i=0; i<len(L); i++) {
        if (strcmp(at(L, i), s))
            return i;
    }
    return -1;
}

char *remove_string(struct List *L, char *s) {
    int pos = find(L, s);
    if (pos < 0)
        return NULL;
    return pop_at(L, pos);
}

int remove_all(struct List *L, char *s) {
    int i, j, count, cap;

    for (i=0, j=0, count=0; i<len(L); i++) {
        if (strcmp(at(L, i), s))
            count++;
        else
            L->_A[j++] = L->_A[i];
    }
    L->_size -= count;
    cap = L->_capacity;
    while (len(L) * SHRINK <= cap && CAPACITY < cap)
        cap /= GROW;
    if (cap <= L->_capacity) {
        char **old = L->_A;
        L->_A = resize(L, cap);
        L->_capacity = cap;
        free(old);
    }
    return count;
}