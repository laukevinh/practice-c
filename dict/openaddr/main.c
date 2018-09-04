#include <stdio.h>
#include "dict.h"
#include <assert.h>

int main(void)
{
    test_new_dict();
    //test_hash();
    //test_get_prime();
    test_resize();
    /*
    test_add();
    test_get();
    test_del();
    */
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
    /*
    printf("(%s,%d)\n", "a", get(d, "a"));
    printf("(%s,%d)\n", "b", get(d, "b"));
    printf("(%s,%d)\n", "c", get(d, "c"));
    printf("(%s,%d)\n", "d", get(d, "d"));
    printf("(%s,%d)\n", "e", get(d, "e"));
    */
    assert(d->n == 4);
    assert(d->m == 4);
    //printf("Tble ele/size: %d/%d\n", d->n, d->m);
    resize_tbl(d);
    //printf("Tble ele/size: %d/%d\n", d->n, d->m);
    assert(d->n == 4);
    assert(d->m == 8);
    add(d, "e", 101);
    //printf("Tble ele/size: %d/%d\n", d->n, d->m);
    assert(d->n == 5);
    assert(d->m == 8);
    assert(get(d, "e") == 101);
    //printf("(%s,%d)\n", "e", get(d, "e"));
    del(d, "a");
    assert(d->n == 4);
    assert(d->m == 8);
    assert(get(d, "a") == -1);
    //printf("Deleted a\n");
    //printf("(%s,%d)\n", "a", get(d, "a"));
    add(d, "a", 197);
    assert(d->n == 5);
    assert(d->m == 8);
    assert(get(d, "a") == 197);
    //printf("(%s,%d)\n", "a", get(d, "a"));

    /*
    char dest[3];
    dest[0] = 'a';
    dest[1] = '\0';
    for (int i=0; i<26; i++) {
        add(d, dest, i);
        dest[0] = dest[0] + 1;
    }
    dest[0] = 'a';
    dest[1] = 'a';
    dest[2] = '\0';
    for (int i=0; i<26; i++) {
        add(d, dest, i);
        dest[1] = dest[1] + 1;
    }
    for (int i=0; i<d->m; i++) {
        struct Node * node = d->head[i];
        printf("(%s,%d)\n", node->key, node->val);
    }
    */
    delete_dict(d);
}

void test_get_prime(void)
{
    printf("Prime: %d\n", pltn(100));
}

/*
void test_add(void)
{
    struct Dict* dict = new_dict(13);
    add(dict, "he", 2);
    add(dict, "hello", 5);
    add(dict, "kevin", 5);
    add(dict, "lissu", 8);
    printf("Test add\n");
    print_items(dict);
    delete_dict(dict);
}

void test_get(void)
{
    struct Dict* dict = new_dict(13);
    add(dict, "he", 2);
    add(dict, "hello", 5);
    add(dict, "kevin", 5);
    add(dict, "lissu", 8);
    printf("Test get kevin: %d\n", get(dict, "kevin"));
    printf("Test get lissu: %d\n", get(dict, "lissu"));
    delete_dict(dict);
}

void test_del(void)
{
    struct Dict* dict = new_dict(13);
    add(dict, "he", 2);
    add(dict, "hello", 5);
    add(dict, "kevin", 5);
    add(dict, "lissu", 8);
    del(dict, "he");
    printf("Test del he\n");
    print_items(dict);
    delete_dict(dict);
}
*/
