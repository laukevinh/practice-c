#include <stdio.h>
#include "graph.h"
#include "queue.h"

int main(void)
{
    //test_adjacency_list();
    test_bfs_1();
    //test_enqueue();
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

void test_adjacency_list(void)
{
    printf("Test adjacency list\n");
    struct Graph * g = new_graph(5);
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

void test_bfs_1(void)
{
    printf("Test two nodes connected\n");
    struct Graph * g = new_graph(10);
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
    add_edge(g, 7, 3);
    add_edge(g, 7, 8);
    add_edge(g, 8, 7);
    print_graph(g);
    for (int i=0; i<g->nVertices; i++)
        for (int j=0; j<g->nVertices; j++)
            printf("Nodes (%d,%d) %s\n", i, j, connected(g, i, j) ? "connect" : "don't connect");
    delete_graph(g);
}

void test_enqueue(void)
{
    printf("Test queue\n");
    struct Graph * g = new_graph(5);
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
    struct Queue * q = new_queue(g->array);
    for (int i=1; i<5; i++)
        enqueue(q, g->array+i);
    print_queue(q);
    delete_queue(q);
    delete_graph(g);
}

