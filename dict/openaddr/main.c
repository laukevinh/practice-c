#include <stdio.h>
#include "dict.h"
#include <assert.h>

int main(void)
{
    test_new_dict();
    //test_hash();
    //test_get_prime();
    test_resize();
}

void test_new_dict(void)
{
    printf("Test new dictionary\n");
    struct Dict* dict = new_dict();
    dict->head[0] = new_node("a", 0);
    dict->head[3] = new_node("d", 3);
    assert(dict->head[0]->val == 0);
    assert(dict->head[2] == NULL);
    assert(dict->head[3]->key == "d");
    delete_dict(dict);
}

void test_hash(void)
{
    printf("Test str hash\n");
    char a[] = "hello";
    char b[] = "kevin";
    char * keys[] = {a , b};
    printf("Test djb2 of %s: %lu\n", a, djb2(a));
    printf("Test djb2 of %s: %lu\n", b, djb2(b));
    printf("Test hash\n");
    int keyct[31];
    for (int i=0; i<31; i++)
        keyct[i]=0;
    for (int i=0; i<1; i++)
        for (int j=0; j<31; j++) {
            int temp = hash(djb2(keys[i]), 31, j);
            printf("Test hash(%s,%d): %d\n", keys[i], j, hash(djb2(keys[i]), 31, j));
            keyct[temp] = keyct[temp] + 1;
        }

    for (int i=0; i<31; i++)
        printf("%d ", keyct[i]);
    printf("Thresholds: %.2f %.2f\n", UPSIZE_THRESHOLD, DOWNSIZE_THRESHOLD);
}

void test_resize(void)
{
    printf("Test resize table\n");
    struct Dict * d = new_dict();
    add(d, "a", 97);
    add(d, "b", 98);
    add(d, "c", 99);
    add(d, "d", 100);
    assert(get(d, "a") == 97);
    assert(get(d, "d") == 100);
    assert(get(d, "e") == -1);
    //assert(d->n == 4);
    //assert(d->m == 4);

    //assert(resize_tbl(d) == 4);
    assert(d->n == 4);
    assert(d->m == 8);

    add(d, "e", 101);
    assert(d->n == 5);
    assert(d->m == 8);
    assert(get(d, "e") == 101);

    del(d, "a");
    assert(d->n == 4);
    assert(d->m == 8);
    assert(get(d, "a") == -1);

    add(d, "a", 197);
    assert(d->n == 5);
    assert(d->m == 8);
    assert(get(d, "a") == 197);
    del(d, "a");
    del(d, "b");
    del(d, "c");
    del(d, "d");
    del(d, "e");
    assert(d->n == 0);
    assert(d->m == 4);
    delete_dict(d);
}

void test_get_prime(void)
{
    printf("Prime: %d\n", pltn(100));
}
