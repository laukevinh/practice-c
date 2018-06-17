/*  Dictionary implementation with chaining.
    Uses division method. No resizing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dict.h"

struct Dict* new_dict(int m)
{
    struct Dict *dict = malloc(sizeof(struct Dict));
    dict->head = malloc(sizeof(struct Node*) * m);
    dict->m = m;
    for (int i=0; i<m; i++)
        *(dict->head + i) = NULL;
    return dict;
}

void delete_dict(struct Dict *dict)
{
    for (int i=0; i<dict->m; i++) {
        struct Node **bucket = dict->head+i;
        struct Node *node = *bucket;
        while (node != NULL) {
            struct Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(dict->head);
    free(dict);
}

struct Node* new_node(char *s, int i)
{
    struct Node *node = malloc(sizeof(struct Node));
    node->key = s;
    node->val = i;
    node->next = NULL;
    return node;
}

void print_items(struct Dict* dict)
{
    for (int i=0; i<dict->m; i++) {
        struct Node *node = *(dict->head+i);
        printf("%3d ", i);
        while (node != NULL) {
            printf(" -> (%s, %d)", node->key, node->val);
            node = node->next;
        }
        printf("\n");
    }
}

int sigdig(int i)
{
    int b = 1;
    while (b < i)
        b *= 10;
    return b;
}

double prehash(char *s)
{
    // takes a string and returns a numeric representation
    double preh = *s;
    char *next = s+1;
    while (*next != '\0') {
        preh = preh * sigdig(*next) + *next;
        next++;
    }
    return preh;
}

int hash(double k, double m)
{
    return fmod(k,m);
}

void add(struct Dict *dict, char *key, int value)
{
    // find if key exists, override or add
    int h = hash(prehash(key), dict->m);
    struct Node** bucket = dict->head+h;
    if (*bucket == NULL) {
        *bucket = new_node(key, value);
    } else {
        struct Node* node = *bucket;
        while (node->next != NULL)
            node = node->next;
        node->next = new_node(key, value);
    }
}

int get(struct Dict *dict, char *key)
{
    int h = hash(prehash(key), dict->m);
    struct Node** bucket = dict->head+h;
    struct Node* node = *bucket;
    while (node != NULL && strcmp(node->key, key) != 0)
        node = node->next;
    if (node == NULL)
        return -1;
    return node->val;
}

void del(struct Dict *dict, char *key)
{
    int h = hash(prehash(key), dict->m);
    struct Node** bucket = dict->head+h;
    struct Node* node = *bucket;
    struct Node* prev = NULL;
    while (node != NULL && strcmp(node->key, key) != 0) {
        prev = node;
        node = node->next;
    }
    if (node == NULL) {
        printf("Err key does not exist\n");
    } else if (prev == NULL) {
        *bucket = node->next;
        free(node);
    } else {
        prev->next = node->next;
        free(node);
    }
}
