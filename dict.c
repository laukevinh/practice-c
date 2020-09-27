#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 17
#define GROW 2
#define SHRINK 4

struct Item {
    char *key;
    int val;
    struct Item *next;
};
struct Dict {
    int n;      /* num of items */
    int m;      /* len of table */
    struct Item **t;    /* table */
};

void resize(struct Dict *, int);
unsigned int hash(char *, int);
struct Dict *newdict(int);
void add(struct Dict *, char *, int);
int exists(struct Dict *, char *);
int get(struct Dict *, char *);
void printdict(struct Dict *);
int primebelow(int);
void del(struct Dict *, char *);

int main(void)
{
    char *words[] = { 
        "pepper", "oyster", "lobster", "copy", "sing", "normal",
        "jokester", "singer", "hash", "dict", "brick", "sick",
        "lick", "trip", "slip", "wear", "ear", "hear", "cat",
        "bat", "mat", "sat", "table", "password", "sesame", "pot",
        "follow", "surprise", "system", "blog", "launch", "give",
        "cat", "icecream", "noisy", "wand", "report", "office",
        "west"
    };
    int numwords, i, j;
    struct Dict *d;

    numwords = sizeof(words) / sizeof(words[0]);
    d = newdict(SIZE);
    add(d, words[0], 1);
    printf("get(%s): %d\n", words[0], get(d, words[0]));
    printf("exists(%s): %d\n", words[0], exists(d, words[0]));
    for (j = 0 ; j < numwords; j++)
        add(d, words[j], j);
    printf("num keys: %d\n", d->n);
    printf("tbl size: %d\n", d->m);
    printdict(d);
    for (j = 0 ; j < numwords * 4 / 5; j++)
        del(d, words[j]);
    printf("tbl size: %d\n", d->m);
    printdict(d);
    return 0;
}

/* talloc:  allocates memory for table */
struct Item **talloc(int m)
{
    return (struct Item **) malloc(sizeof(struct Item *) * m);
}

/* dalloc:  allocates memory for dictionary */
struct Dict *dalloc(void)
{
    return (struct Dict *) malloc(sizeof(struct Dict));
}

/* newdict: creates new dictionary with initialized values */
struct Dict *newdict(int m)
{
    struct Dict *d;
    int i;

    d = dalloc();
    d->n = 0;
    d->m = m;
    d->t = talloc(d->m);
    for (i = 0; i < d->m; i++)
        d->t[i] = NULL;
    return d;
}

/* newitem: creates new item (key, value) */
struct Item *newitem(char *key, int val)
{
    struct Item *item;

    item = (struct Item *) malloc(sizeof(struct Item));
    item->key = (char *) malloc(sizeof(char) * strlen(key) + 1);
    strcpy(item->key, key);
    item->val = val;
    item->next = NULL;
    return item;
}

/* Not sure why DJB choose these constants, but it works
    well on strings. Note unsigned ints don't overflow,
    they wrap around, so really long strlens are still okay.*/
unsigned int DJBprehash(char *str) 
{
    unsigned int hash = 5381;

    for ( ; *str != '\0'; ++str)
        hash = ((hash << 5) + hash) + (*str);
    return hash;
}

/* hash: using the division method because it's simple */
unsigned int hash(char *str, int m)
{
    return DJBprehash(str) % m;
}

/* add: adds new item (key, value) to dictionary. if
    total number of items n starts getting bigger than
    table size m, expand table size to next prime number
    just under 2 * m. */
void add(struct Dict *d, char *key, int val)
{
    int r;
    struct Item *ip, *prev;

    if (d->n + 1 > d->m)
        resize(d, primebelow(d->m * 2));
    r = hash(key, d->m);
    for (prev = ip = d->t[r]; ip!=NULL; prev=ip, ip=ip->next) {
        if (strcmp(ip->key, key) == 0) {
            ip->val = val;
            break;
        }
    }
    if (prev == NULL) {   /* key not found, add new */
        d->t[r] = newitem(key, val);
        d->n++;
    } else if (ip == NULL) {
        prev->next = newitem(key, val);
        d->n++;
    }
}

int exists(struct Dict *d, char *key)
{
    int r;
    struct Item *ip;

    r = hash(key, d->m);
    for (ip = d->t[r]; ip != NULL; ip = ip->next)
        if (strcmp(ip->key, key) == 0)
            return 1;
    return 0;
}

int get(struct Dict *d, char *key)
{
    int r;
    struct Item *ip;

    r = hash(key, d->m);
    for (ip = d->t[r]; ip != NULL; ip = ip->next)
        if (strcmp(ip->key, key) == 0)
            return ip->val;
    printf("%s not found\n", key);
    return -1;
}

/* resize: copies over old dict to new */
void resize(struct Dict *d, int m)
{
    struct Dict *e;
    struct Item *ip;
    int i;

    e = newdict(m);
    for (i = 0; i < d->m; i++) {
        for (ip = d->t[i]; ip != NULL; ip = d->t[i]) {
            add(e, ip->key, ip->val);
            d->t[i] = ip->next;
            free(ip->key);
            free(ip);
        }
    }
    free(d->t);
    d->t = e->t;
    d->n = e->n;
    d->m = e->m;
    free(e);
}

void printdict(struct Dict *d)
{
    int len, i;
    struct Item *ip;

    for (i = 0; i < d->m; i++) {
        len = 0;
        for (ip = d->t[i]; ip != NULL; ip = ip->next)
            len++;
        printf("%3d %3d: ", i, len);
        for (ip = d->t[i]; ip != NULL; ip = ip->next)
            printf("%s ", ip->key);
        printf("\n");
    }
}

int primebelow(int n)
{
    enum boolean { FALSE, TRUE };
    int i, a;
    int prime[n+1];

    for (i = 2; i < n+1; i++)
        prime[i] = TRUE;
    for (i = 2; i < n+1; i++)
        if (prime[i])
            for (a = 2*i; a < n+1; a+=i)
                prime[a] = FALSE;
    for (i=n; !prime[i]; i--)
        ;
    return i;
}

/* del: deletes item from dict given key. If number of 
    items n becomes 1/4 of table size m, resize table
    size to largest prime number under m / 2. */
void del(struct Dict *d, char *key)
{
    int r;
    struct Item *ip, *prev;

    r = hash(key, d->m);
    for (prev=ip=d->t[r]; ip!=NULL; prev=ip, ip=ip->next)
        if (strcmp(key, ip->key) == 0)
            break;
    if (ip == NULL)
        printf("key %s doesn't exist\n", key);
    else {
        if (prev == ip) {
            d->t[r] = ip->next;
        } else {
            prev->next = ip->next;
        }
        free(ip->key);
        free(ip);
        d->n--;
        if (d->n * SHRINK < d->m && d->m / 2 > SIZE)
            resize(d, primebelow(d->m / 2));
    }
}