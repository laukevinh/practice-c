#include <stdio.h>
#include <assert.h>
#include "graph.h"

int main(void)
{
    //test_adjacency_list();
    test_adjacency_matrix();
    test_shortest_path();
    test_is_cyclic();
    test_topological_sort();
    //test_stack();
    return 0;
}

/*  Test following graph

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

void test_adjacency_matrix(void)
{
    printf("Test adjacency matrix\n");
    struct Graph * g = new_graph(8, 0);
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
    print_graph(g);
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
