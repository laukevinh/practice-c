#include <stdio.h>
#include "graph.h"
#include "queue.h"

int main(void)
{
    //test_adjacency_list();
    //test_shortest_path();
    test_cyclic_graph();
    test_acyclic_graph();
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

void test_shortest_path(void)
{
    printf("Test shortest path using bfs\n");
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
    bfs(g, 5, 0);
    delete_graph(g);
}

void test_cyclic_graph(void)
{
    printf("Test for cycles\n");
    struct Graph * g = new_graph(5);
    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 1, 3);
    add_edge(g, 2, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 4);
    add_edge(g, 4, 1);
    print_graph(g);
    int discovered[g->nVertices];
    int processed[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        discovered[i] = 0;
        processed[i] = 0;
    }
    discovered[0] = processed[0] = 1;
    printf("%s\n", is_cyclic(g, 0, discovered, processed)? "Cycle detected" : "No cycle");
    delete_graph(g);

    struct Graph * h = new_graph(3);
    add_edge(h, 0, 1);
    add_edge(h, 1, 2);
    add_edge(h, 2, 0);
    print_graph(h);
    int d[h->nVertices];
    int p[h->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        d[i] = 0;
        p[i] = 0;
    }
    d[0] = p[0] = 1;
    printf("%s\n", is_cyclic(h, 0, d, p)? "Cycle detected" : "No cycle");
    delete_graph(h);
}

void test_acyclic_graph(void)
{
    printf("Test for no cycles\n");
    struct Graph * g = new_graph(5);
    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 1, 3);
    add_edge(g, 2, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 4);
    print_graph(g);
    int discovered[g->nVertices];
    int processed[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        discovered[i] = 0;
        processed[i] = 0;
    }
    discovered[0] = processed[0] = 1;
    printf("%s\n", is_cyclic(g, 0, discovered, processed)? "Cycle detected" : "No cycle");
    delete_graph(g);
}

void test_stack(void)
{
    printf("Test stack\n");
    struct Graph * g = new_graph(5);
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
