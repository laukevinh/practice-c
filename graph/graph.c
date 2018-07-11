#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/*  Adjacency List representation

    +---------------+
    | int nVertices |
    +---------------+        +-----------+        +------+
    | pter to array | -----> | AdjList 0 | -----> | NULL |
    +---------------+        +-----------+        +------+        +------+
                             | AdjList 1 | ---------------------> | NULL |
                             +-----------+        +------+        +------+
                             | AdjList 2 | -----> | NULL |
                             +-----------+        +------+
                             | ...       |
                             +-----------+

    Set aside storage for array of linkedlist pointers
    and initialize them to NULL.

    Syntax g->array[i].head is the same as

        struct AdjList * aj = g->array;
        struct AdjList temp = *(aj+i);
        temp.head = NULL;

    which is also the same as

        (g->array+i)->head = NULL;
*/

struct Graph * new_graph(int nVertices)
{
    struct Graph * g = malloc(sizeof(struct Graph));
    g->nVertices = nVertices;

    g->array = malloc(sizeof(struct AdjList) * nVertices);

    for (int i=0; i<nVertices; i++)
        g->array[i].head = NULL;

    return g;
}

/* New adjacency list node */

struct AdjListNode * new_node(int data)
{
    struct AdjListNode * node = malloc(sizeof(struct AdjListNode));
    node->data = data;
    node->next = NULL;
    return node;
}

/*  add an edge between vertex v1 and vertex v2 */

void add_edge(struct Graph * g, int v1, int v2)
{
    struct AdjListNode * node = new_node(v2);
    node->next = g->array[v1].head;
    g->array[v1].head = node;
}

/* Utility function to delete graph */

void delete_graph(struct Graph * g)
{
    for (int i=0; i<g->nVertices; i++)
        while (g->array[i].head != NULL) {
            struct AdjListNode * temp = g->array[i].head;
            g->array[i].head = temp->next;
            free(temp);
        }
    free(g->array);
    free(g);
}

/* Utility function to print graph */

void print_graph(struct Graph * g)
{
    for (int i=0; i<g->nVertices; i++) {
        printf("Vertex %d list\n", i);
        struct AdjListNode * crawl = g->array[i].head;
        while (crawl != NULL) {
            printf("%d ", crawl->data);
            crawl = crawl->next;
        }
        printf("\n");
    }
}

/* Breadth first search */

int bfs(struct Graph *g, int start, int dest)
{
    return 0;
}

/* Returns whether two nodes are connected */

int connected(struct Graph * g, int v1, int v2)
{
    return 0;
}
