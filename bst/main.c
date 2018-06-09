#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void run_tests(void);

int main(void)
{
    run_tests();
    return 0;
}

void run_tests(void)
{
    test_new_node();
    test_insert();
    test_is_in_tree();
    test_count();
    test_height();
    test_min();
    test_max();
    test_successor();
    /*
    test_resize();
    test_append();
    test_push();
    test_pop();
    test_pop_front();
    test_insert();
    test_delete();
    test_update();
    test_find();
    */
}
