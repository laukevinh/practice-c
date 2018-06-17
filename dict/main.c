#include <stdio.h>
#include "dict.h"

int main(void)
{
    test_new_dict();
    test_prehash();
    test_add();
    test_get();
    test_del();
}

void test_new_dict(void)
{
    struct Dict* dict = new_dict(13);
    for (int i=0; i<dict->m; i+=2)
        *(dict->head+i) = new_node("node", i);
    printf("Printing bucket, nodes\n");
    print_items(dict);
    delete_dict(dict);
}

void test_prehash(void)
{
    char s[] = "hello";
    printf("Test prehash of %s: %.0f\n", s, prehash(s));
    printf("Test hash of %s: %d\n", s, hash(prehash(s), 13));
}

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

