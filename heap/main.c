#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

void run_tests(void);

int main(void)
{
    run_tests();
    return 0;
}

void run_tests(void)
{
    //test_heap();
    //test_get_children();
    test_max_heapify();
    test_pop_max();
}
