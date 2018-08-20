#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "queue.h"
#include "heap.h"

int main(void)
{
    //test_adjacency_list();
    test_shortest_path();
    test_is_cyclic();
    test_topological_sort();
    test_connected_components();
    test_two_color();
    test_weighted_graph();
    test_prim_mst();
    test_heap();
    //test_stack();
    return 0;
}

/*  Test following undirected graph

    +---+     +---+
    | 0 |-----| 1 |-----+
    +---+     +---+     |
      |     _/  |     +---+
      |   _/    |     | 2 |
      |  /      |     +---+
    +---+     +---+     | 
    | 4 |-----| 3 |-----+
    +---+     +---+
*/

void test_adjacency_list(void)
{
    printf("Test adjacency list\n");
    struct Graph * g = new_graph(5, 0);
    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 1, 0);
    add_edge(g, 1, 2);
    add_edge(g, 1, 3);
    add_edge(g, 1, 4);
    add_edge(g, 2, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 1);
    add_edge(g, 3, 2);
    add_edge(g, 3, 4);
    add_edge(g, 4, 0);
    add_edge(g, 4, 3);
    add_edge(g, 4, 1);
    print_graph(g);
    delete_graph(g);
}

/*  Test following undirected graph

    +---+   +---+   +---+
    | 0 |---| 1 |---| 2 |
    +---+   +---+   +---+
              |    / 
              |   / 
              |  /
    +---+   +---+   +---+
    | 4 |---| 3 |---| 7 |
    +---+   +---+   +---+
      |       |       |
      |       |       |
      |       |       |
    +---+   +---+   +---+
    | 5 |---| 6 |---| 8 |
    +---+   +---+   +---+

*/

void test_shortest_path(void)
{
    printf("Test shortest path using bfs\n");
    struct Graph * g = new_graph(10, 0);
    add_edge(g, 0, 1);
    add_edge(g, 1, 0);
    add_edge(g, 1, 2);
    add_edge(g, 1, 3);
    add_edge(g, 2, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 1);
    add_edge(g, 3, 2);
    add_edge(g, 3, 4);
    add_edge(g, 3, 6);
    add_edge(g, 3, 7);
    add_edge(g, 4, 3);
    add_edge(g, 4, 5);
    add_edge(g, 5, 4);
    add_edge(g, 5, 6);
    add_edge(g, 6, 3);
    add_edge(g, 6, 5);
    add_edge(g, 6, 8);
    add_edge(g, 7, 3);
    add_edge(g, 7, 8);
    add_edge(g, 8, 6);
    add_edge(g, 8, 7);
    shortest_path(g, 5, 0);
    shortest_path(g, 9, 0);
    shortest_path(g, 2, 5);
    shortest_path(g, 5, 8);
    delete_graph(g);
}

void test_is_cyclic(void)
{
    printf("Test for cycles\n");
    struct Graph * g = new_graph(5, 1);
    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 1, 3);
    add_edge(g, 2, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 4);
    add_edge(g, 4, 1);
    assert(is_cyclic(g) == 1);
    delete_graph(g);

    g = new_graph(3, 1);
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0);
    assert(is_cyclic(g) == 1);
    delete_graph(g);

    g = new_graph(5, 1);
    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 1, 3);
    add_edge(g, 2, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 4);
    assert(is_cyclic(g) == 0);
    delete_graph(g);

    g = new_graph(5, 1);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 3, 4);
    add_edge(g, 4, 3);
    assert(is_cyclic(g) == 1);
    delete_graph(g);
    
    g = new_graph(5, 0);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 0);
    add_edge(g, 2, 0);
    add_edge(g, 3, 4);
    add_edge(g, 4, 3);
    assert(is_cyclic(g) == 0);
    delete_graph(g);

    g = new_graph(5, 0);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 0);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0);
    add_edge(g, 2, 1);
    add_edge(g, 3, 4);
    add_edge(g, 4, 3);
    assert(is_cyclic(g) == 1);
    delete_graph(g);
}

void test_topological_sort(void)
{
    printf("Test topological sort\n");
    struct Graph * g = new_graph(5, 1);
    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 1, 3);
    add_edge(g, 2, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 4);
    topological_sort(g, 0);
    delete_graph(g);
}

/*  test the following undirected graph

    +---+   +---+   +---+
    | 0 |---| 1 |---| 2 |
    +---+   +---+   +---+

    +---+   +---+   +---+
    | 5 |---| 4 |---| 3 |
    +---+   +---+   +---+

    +---+   +---+   +---+
    | 6 |---| 8 |---| 7 |
    +---+   +---+   +---+
*/

    
void test_connected_components(void)
{
    printf("Test connected components\n");
    struct Graph * g = new_graph(9, 1);
    add_edge(g, 0, 1);
    add_edge(g, 1, 0);
    add_edge(g, 1, 2);
    add_edge(g, 2, 1);

    add_edge(g, 3, 4);
    add_edge(g, 4, 3);
    add_edge(g, 4, 5);
    add_edge(g, 5, 4);

    add_edge(g, 6, 8);
    add_edge(g, 8, 6);
    add_edge(g, 7, 8);
    add_edge(g, 8, 7);
    assert(connected_components(g) == 3);
    delete_graph(g);
}

/*  test the following undirected graph

    bipartite
    +---+   +---+   +---+
    | 0 |---| 1 |---| 2 |   
    +---+   +---+   +---+

    not bipartite
         +---+
      +--| 0 |--+
      |  +---+  |
      |         |
    +---+     +---+
    | 1 |-----| 2 |
    +---+     +---+

*/

void test_two_color(void)
{
    printf("Test two color\n");
    struct Graph * g = new_graph(5, 0);
    add_edge(g, 0, 1);
    add_edge(g, 1, 0);
    add_edge(g, 1, 2);
    add_edge(g, 2, 1);
    two_color(g);

    add_edge(g, 0, 2);
    add_edge(g, 2, 0);
    two_color(g);
    delete_graph(g);
}

/*  test following directed weighted graph
         +---+
         | 0 |   
         +---+
        /     \
       /       \
    +---+    +---+
    | 1 |----| 2 |
    +---+    +---+

*/

void test_weighted_graph(void)
{
    printf("Test weighted graph\n");
    struct Graph * g = new_graph(5, 1);
    add_wt_edge(g, 0, 1, 2);
    add_wt_edge(g, 1, 2, 4);
    add_wt_edge(g, 2, 0, 2);

    assert(g->array[0].head->weight == 2);
    assert(g->array[1].head->weight == 4);
    delete_graph(g);
}

/*  test following undirected graph

     0

    1
         4
    2

     3

*/

void test_prim_mst(void)
{
    printf("Test spanning tree\n");
    struct Graph * g = new_graph(5, 0);
    add_wt_edge(g, 0, 1, 1);
    add_wt_edge(g, 0, 2, 3);
    add_wt_edge(g, 0, 3, 5);
    add_wt_edge(g, 0, 4, 2);

    add_wt_edge(g, 1, 0, 1);
    add_wt_edge(g, 1, 2, 1);
    add_wt_edge(g, 1, 3, 3);
    add_wt_edge(g, 1, 4, 2);

    add_wt_edge(g, 2, 0, 3);
    add_wt_edge(g, 2, 1, 1);
    add_wt_edge(g, 2, 3, 1);
    add_wt_edge(g, 2, 4, 2);

    add_wt_edge(g, 3, 0, 5);
    add_wt_edge(g, 3, 1, 3);
    add_wt_edge(g, 3, 2, 1);
    add_wt_edge(g, 3, 4, 2);

    add_wt_edge(g, 4, 0, 2);
    add_wt_edge(g, 4, 1, 2);
    add_wt_edge(g, 4, 2, 2);
    add_wt_edge(g, 4, 3, 2);
    
    prim_mst(g, 0);
    prim_mst(g, 1); 
    delete_graph(g);
}

void test_heap(void)
{
    printf("Test heap\n");
    struct Heap * h = new_heap();
    for (int i=0; i<32; i++)
        insert_heap(h, i, i, i);
    insert_heap(h, 99, 99, 99);
    //  test inserts maintain max heap prop
    assert(h->edges[0].wt == 99);
    assert(h->edges[1].wt == 31);
    //  test capacity and size expand
    assert(h->capacity == 64);
    assert(h->size == 33);

    for (int i=0; i<18; i++)
        extract_max(h);
    //  test capacity and size contract after pops
    assert(h->capacity == 32);
    assert(h->size == 15);

    printf("Scramble heap\n");
    for (int i=0; i<h->size; i++)
        h->edges[i].v1 = h->edges[i].v2 = h->edges[i].wt = i;

    printf("Build max heap\n");
    build_max_heap(h);
    assert(h->edges[0].wt == 14);
    assert(h->edges[h->size-1].wt == 0);
    
    printf("heap sort\n");
    heap_sort(h);
    for (int i=0; i<h->size; i++)
        assert(h->edges[i].wt == i);
    delete_heap(h);

    printf("Test min heap\n");
    h = new_heap();
    for (int i=0; i<32; i++)
        insert_min_heap(h, i, i, i);
    insert_min_heap(h, 99, 99, 99);
    //  test inserts maintain min heap prop
    assert(h->edges[0].wt == 0);
    assert(h->edges[1].wt == 1);
    //  test capacity and size expand
    assert(h->capacity == 64);
    assert(h->size == 33);

    for (int i=0; i<18; i++)
        extract_min(h);
    //  test capacity and size contract after pops
    assert(h->capacity == 32);
    assert(h->size == 15);

    printf("Scramble heap\n");
    for (int i=0; i<h->size; i++)
        h->edges[i].v1 = h->edges[i].v2 = h->edges[i].wt = h->size-1-i;

    printf("Build min heap\n");
    build_min_heap(h);
    assert(h->edges[0].wt == 0);
    assert(h->edges[h->size-1].wt == 14);
    
    delete_heap(h);
}

void test_stack(void)
{
    printf("Test stack\n");
    struct Graph * g = new_graph(5, 0);
    struct Queue * stack = new_queue(NULL);
    for (int i=0; i<g->nVertices; i++) {
        push(stack, g->array+i);
    }

    // pop stack
    while (stack->head != NULL) {
        printf("%d ", (int) (pop(stack) - g->array));
    }

    printf("\n");
    printf("stack len: %d\n", length(stack));
    delete_queue(stack);
    delete_graph(g);
}
