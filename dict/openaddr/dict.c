/*  Dictionary implementation with open addr.
    Uses division method. No resizing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dict.h"
#define TRUE 1
#define FALSE 0

static struct Node DELETED;

int pltn(int n)
{
    int sieve[n];
    for (int i=0; i<n; i++)
        sieve[i] = TRUE;
    int p = 2;
    while (p < n) {
        if (sieve[p++] == TRUE)
            for (int i=p; i<n; i++)
                if (i % p == 0)
                    sieve[i] = FALSE;
    }
    for (int i=n-1; i>=0; i--)
        if (sieve[i] == TRUE)
            return i;
    return 0;
}

struct Dict * new_dict(void)
{
    struct Dict * d = malloc(sizeof(struct Dict));
    d->head = malloc(sizeof(struct Node * ) * MIN_CAPACITY);
    d->m = MIN_CAPACITY;
    d->n = 0;
    for (int i=0; i<MIN_CAPACITY; i++)
        *(d->head + i) = NULL;
    return d;
}

void delete_dict(struct Dict * d)
{
    for (int i=0; i<d->m; i++)
        if (*(d->head+i) != NULL)
            free(*(d->head+i));
    free(d->head);
    free(d);
}

struct Node * new_node(char *s, int i)
{
    struct Node * node = malloc(sizeof(struct Node));
    node->key = s;
    node->val = i;
    return node;
}

unsigned long djb2(unsigned char *str)
{
    unsigned long h = 5381;
    int c;
    while (c = *str++)
        h = ((h << 5) + h) + c; /* hash * 33 + c */
    return h;
}

int hash1(unsigned long k, int tblsize)
{
    return fmod(k, tblsize);
}

/*  Linear probing is like parking your car.
    You keep driving, checking each slot one by one.
    Prone to clustering.
    
    hash(key, trial) = (h1(key) + trial) mod tblsize;

    where h1 is a regular hash function like
    h1(key) = key mod tblsize;

*/
int lin_probe(unsigned long k, int tblsize, int t)
{
    return fmod(hash1(k,tblsize) + t, tblsize);
}

/*  Quadratic probing spaces it out a bit more.
    
    hash(key, trial) = (h1(key) + trial^2) mod tblsize;
*/
int quad_probe(unsigned long k, int tblsize, int t)
{
    return fmod(hash1(k,tblsize) + t * t, tblsize);
}

int hash2(unsigned long k, int tblsize)
{
    int PRIME = pltn(tblsize);
    return PRIME - (k % PRIME);
}

/*  Double hashing probe uses a second hash to decide
    where to place.
    
    hash(key, trial) = (h1(key) + trial * h2(key)) mod tblsize;

    where h2 is relatively prime to tblsize, meaning they
    do not share any common factors except for 1. If h2 is odd
    and tblsize is some 2^r, then we should be good.
*/
int dblh_probe(unsigned long k, int tblsize, int t)
{
    return fmod(hash1(k,tblsize) + t * hash2(k,tblsize), tblsize);
}

int hash(unsigned long k, int tblsize, int t)
{
    return fmod(hash1(k,tblsize) + t * hash2(k,tblsize), tblsize);
}

/*  1. pre-hash key (string)
    2. double hash trial 0
    3. if collision try again until no collision
    4. if NULL the key doesn't exist
*/

struct Node ** get_util(struct Dict * dict, char * key)
{
    int t = 0;
    int h = dblh_probe(djb2(key), dict->m, t);
    struct Node * curr = *(dict->head+h);
    while (TRUE) {
        if (t >= dict->m)
            break;
        if (curr == NULL)
            break;
        if (curr != &DELETED && strcmp(curr->key, key) == 0)
            break;
        h = dblh_probe(djb2(key), dict->m, ++t);
        curr = *(dict->head + h);
    }
    //return (t >= dict->m) ? NULL : curr;
    return (t >= dict->m) ? NULL : dict->head + h;
}

int get(struct Dict *dict, char *key)
{
    /*
    struct Node * node = get_util(dict, key);
    if (node == NULL) {
        printf("Key %s doesn't exist\n", key);
        return -1;
    } else {
        return node->val;
    }
    */
    struct Node ** node = get_util(dict, key);
    if (node == NULL) {
        printf("Key %s doesn't exist\n", key);
        return -1;
    } else {
        return (*node)->val;
    }
}

void add_util(struct Dict * dict, char *key, int value, struct Node * node)
{
    int t = 0;
    int h = dblh_probe(djb2(key), dict->m, t);
    struct Node * curr = *(dict->head+h);
    while (TRUE) {
        if (t >= dict->m)
            break;
        if (curr == NULL)
            break;
        if (curr == &DELETED)
            break;
        h = dblh_probe(djb2(key), dict->m, ++t);
        curr = *(dict->head + h);
    }
    if (t >= dict->m) {
        printf("Dictionary full\n");
    } else {
        dict->head[h] = node;
        dict->n++;
    }
}

void add(struct Dict * dict, char *key, int value)
{
    /*
    int t = 0;
    int h = dblh_probe(djb2(key), dict->m, t);
    struct Node * curr = *(dict->head+h);
    while (TRUE) {
        if (t >= dict->m)
            break;
        if (curr == NULL)
            break;
        if (curr == &DELETED)
            break;
        h = dblh_probe(djb2(key), dict->m, ++t);
        curr = *(dict->head + h);
    }
    if (t >= dict->m) {
        printf("Dictionary full\n");
    } else {
        dict->head[h] = new_node(key, value);
        dict->n++;
    }
    */
    add_util(dict, key, value, new_node(key, value));
}

void del(struct Dict *dict, char *key)
{
    /*
    int t = 0;
    int h = dblh_probe(djb2(key), dict->m, t);
    struct Node * curr = *(dict->head+h);
    while (TRUE) {
        if (t >= dict->m)
            break;
        if (curr == NULL)
            break;
        if (curr != &DELETED && strcmp(curr->key, key) == 0)
            break;
        h = dblh_probe(djb2(key), dict->m, ++t);
        curr = *(dict->head + h);
    }
    if (curr == NULL || t >= dict->m) {
        printf("Key %s doesn't exist\n", key);
    } else {
        free(dict->head[h]);
        *(dict->head+h) = &DELETED;
        dict->n--;
    }
    */
    struct Node ** node = get_util(dict, key);
    if (node == NULL) {
        printf("Key %s doesn't exist\n", key);
    } else {
        free(*node);
        *node = &DELETED;
        dict->n--;
    }
}

int resize_tbl(struct Dict * d)
{
    int old_m = d->m;
    int old_n = d->n;
    int alpha = d->n / d->m;
    if (alpha > UPSIZE_THRESHOLD) {
        d->m = d->m * RESIZE_FACTOR;
        d->n = 0;
        struct Node ** old_head = d->head;
        d->head = malloc(sizeof(struct Node * ) * d->m);
        for (int i=0; i<d->m; i++)
            *(d->head + i) = NULL;
        for (int i=0; i<old_m; i++) {
            struct Node * temp = *(old_head+i);
            add_util(d, temp->key, temp->val, *(old_head+i)); 
        }
        free(old_head);
    } else if (alpha < DOWNSIZE_THRESHOLD && d->m / RESIZE_FACTOR > MIN_CAPACITY) {
        d->m = d->m / RESIZE_FACTOR;
        d->n = 0;
        struct Node ** old_head = d->head;
        d->head = malloc(sizeof(struct Node * ) * d->m);
        for (int i=0; i<d->m; i++)
            *(d->head + i) = NULL;
        for (int i=0; i<old_m; i++) {
            struct Node * temp = *(old_head+i);
            if (temp != NULL && temp != &DELETED)
                add_util(d, temp->key, temp->val, *(old_head+i)); 
        }
        free(old_head);
    }
}
