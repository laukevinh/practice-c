#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
};

struct LinkedList {
    struct Node *head;
};

struct LinkedList *newlist(void);
void append(struct LinkedList *, int);
int front(struct LinkedList *);
int back(struct LinkedList *);
int len(struct LinkedList *);
int empty(struct LinkedList *);
int at(struct LinkedList *, int);
void prepend(struct LinkedList *, int);
void printlist(struct LinkedList *);
int popfront(struct LinkedList *);
int popback(struct LinkedList *);
int insert(struct LinkedList *, int, int);
int delete(struct LinkedList *, int);
int at_from_end(struct LinkedList *, int);
void reverse(struct LinkedList *);
int delete_val(struct LinkedList *, int);

int main(void)
{
    struct LinkedList *llp;
    int i;

    llp = newlist();
    append(llp, 0);
    printf("front: %d\n", llp->head->val);
    printf("front: %d\n", front(llp));
    for (i = 0; i < 10; i++)
        append(llp, i);
    printf("back:  %d\n", back(llp));
    printf("len:   %d\n", len(llp));
    printf("at(%d): %d\n", 0, at(llp, 0));
    printf("at(%d): %d\n", 3, at(llp, 3));
    printf("at(%d): %d\n", -1, at(llp, -1));
    printf("at(%d): %d\n", 11, at(llp, 11));
    prepend(llp, 100);
    printf("front: %d\n", front(llp));
    printlist(llp);
    printf("\npop front: %d\n", popfront(llp));
    printf("pop back: %d\n", popback(llp));
    while (!empty(llp))
        printf("pop front: %d\n", popfront(llp));
    printf("pop front: %d\n", popfront(llp));
    printf("pop back: %d\n", popback(llp));
    for (i = 0; i < 10; i++)
        append(llp, i);
    insert(llp, -1, 100);   /* index error */
    insert(llp, 10, 100);   /* index error */
    insert(llp, 9, 100);
    printlist(llp);
    printf("\n");
    delete(llp, 9);         /* delete previous insert */
    delete(llp, 9);         /* delete last item */
    delete(llp, 0);         /* delete first item */
    printlist(llp);
    printf("\nat_from_end(%d): %d\n", 3, at_from_end(llp, 3));
    printf("at_from_end(%d): %d\n", 8, at_from_end(llp, 8));
    reverse(llp);
    printlist(llp);
    printf("\n");
    prepend(llp, 8);
    delete_val(llp, 2);
    delete_val(llp, 1);
    delete_val(llp, 8);
    delete_val(llp, 100);
    printlist(llp);
    printf("\n");

    return 0;
}

struct LinkedList *newlist(void)
{
    struct LinkedList *llp;

    llp = (struct LinkedList *) malloc(sizeof(struct LinkedList));
    llp->head = NULL;
    return llp;
}

void append(struct LinkedList *llp, int i)
{
    struct Node *np, *newnode(int);

    if (llp->head == NULL)
        llp->head = newnode(i);
    else {
        for (np=llp->head; np->next!=NULL; np=np->next)
            ;
        np->next = newnode(i);
    }
}

struct Node *newnode(int i)
{
    struct Node *node;

    node = (struct Node *) malloc(sizeof(struct Node));
    node->val = i;
    node->next = NULL;
    return node;
}

int front(struct LinkedList *llp)
{
    if (llp->head == NULL) {
        printf("Error: Empty list\n");
        return -1;
    }
    return llp->head->val;
}

int back(struct LinkedList *llp)
{
    struct Node *np;

    if (llp->head == NULL) {
        printf("Error: Empty list\n");
        return -1;
    }
    for (np=llp->head; np->next!=NULL; np=np->next)
        ;
    return np->val;
}

int len(struct LinkedList *llp)
{
    struct Node *np;
    int i;

    for (i=0, np=llp->head; np!=NULL; i++, np=np->next)
        ;
    return i;
}

int empty(struct LinkedList *llp)
{
    return (llp->head == NULL);
}

int at(struct LinkedList *llp, int idx)
{
    int empty(struct LinkedList *), i;
    struct Node *np;
    
    if (empty(llp)) {
        printf("Error: Empty list\n");
        return -1;
    }
    for (i=0, np=llp->head; i<idx && np!=NULL; i++, np=np->next)
        ;
    if (i != idx || np == NULL) {
        printf("Error: Index %d out of bounds\n", idx);
        return -1;
    }
    return np->val;
}

void prepend(struct LinkedList *llp, int i)
{
    struct Node *node, *newnode(int);

    node = newnode(i);
    node->next = llp->head;
    llp->head = node;
}

void printlist(struct LinkedList *llp)
{
    struct Node *np;

    for (np=llp->head; np!=NULL; np=np->next)
        printf("%d ", np->val);
}

int popfront(struct LinkedList *llp)
{
    struct Node *np;
    int i;

    if (empty(llp)) {
        printf("Error: Empty list\n");
        return -1;
    }
    np = llp->head;
    llp->head = np->next;
    i = np->val;
    free(np);
    return i;
}

int popback(struct LinkedList *llp)
{
    struct Node *prev, *np;
    int i;

    if (empty(llp)) {
        printf("Error: Empty list\n");
        return -1;
    }
    prev = np = llp->head;
    while(np->next != NULL) {
        prev = np;
        np = np->next;
    }
    if (prev == np)
        llp->head = np->next;
    else
        prev->next = np->next;
    i = np->val;
    free(np);
    return i;
}

int insert(struct LinkedList *llp, int idx, int i)
{
    struct Node *prev, *np, *newnode(int);
    int j;

    prev = np = llp->head;
    for (j = 0; j < idx && np != NULL; j++) {
        prev = np;
        np = np->next;
    }
    if (j != idx || np == NULL) {
        printf("Error: Index %d out of bounds\n", idx);
        return -1;
    }
    prev->next = newnode(i);
    prev->next->next = np;
    return 0;
}

int delete(struct LinkedList *llp, int idx)
{
    struct Node *prev, *np;
    int i;

    prev = np = llp->head;
    for (i = 0; i < idx && np != NULL; i++) {
        prev = np;
        np = np->next;
    }
    if (i != idx || np == NULL) {
        printf("Error: Index %d out of bounds\n", idx);
        return -1;
    }
    if (prev == np)
        llp->head = np->next;
    else
        prev->next = np->next;
    i = np->val;
    free(np);
    return i;
}

int at_from_end(struct LinkedList *llp, int i)
{
    int listlen, at(struct LinkedList *, int);

    if (i >= (listlen = len(llp))) {
        printf("Error: Index %d from end is out of bounds\n", i);
        return -1;
    }
    return at(llp, listlen - i - 1);
}

void reverse(struct LinkedList *llp)
{
    struct Node *prev, *np, *nnp;

    prev = NULL;
    np = nnp = llp->head;
    while (np != NULL) {
        nnp = np->next;
        np->next = prev;
        prev = np;
        np = nnp;
    }
    llp->head = prev;
}

int delete_val(struct LinkedList *llp, int i)
{
    struct Node *prev, *np;

    prev = np = llp->head;
    while (np != NULL && np->val != i) {
        prev = np;
        np = np->next;
    }
    if (np == NULL)
        return -1;      /* not found */
    if (prev == np)
        llp->head = np->next;
    else
        prev->next = np->next;
    i = np->val;
    free(np);
    return 0;
}