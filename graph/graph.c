#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "queue.h"
#define TRUE 1
#define FALSE 0

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

/* Returns whether two nodes are connected */

int connected(struct Graph * g, int v1, int v2)
{
    struct Queue * q = new_queue(g->array+v1);

    int discovered[g->nVertices];
    for (int i=0; i<g->nVertices; i++)
        discovered[i] = FALSE;
    discovered[v1] = TRUE;

    while (q->head != NULL) {
        struct AdjList * curr = dequeue(q);
        struct AdjListNode * crawl = curr->head;
        while (crawl != NULL) {
            if (crawl->data == v2) {
                return TRUE;
            }
            if (!discovered[crawl->data]) {
                enqueue(q, g->array+crawl->data);
                discovered[crawl->data] = TRUE;
            }
            crawl = crawl->next;
        }
    }
    delete_queue(q);
    return FALSE;
}

/*  Breadth first search 

    Use queue to process each vertex. Keep track of
    discovered vertices to avoid revisiting. 
    
    If each vertex is allowed one parent, where parent
    is defined as the vertex that discovers it, then 
    one of the shortest paths between two vertices is 
    the list of parents from vertex 2 to vertex 1. 

    Vertex 1's parent is NULL (in this case it's -1).
    So recursively print parents from vertex 2 until NULL.
*/

/* prints shortest path using parents */

void print_path(int * parent, int node)
{
    if (parent[node] >= 0) {
        print_path(parent, parent[node]);
        printf("%d ", node);
    } else {
        printf("root ");
    }
}

int bfs(struct Graph *g, int v1, int v2)
{
    struct Queue * q = new_queue(g->array+v1);

    int discovered[g->nVertices];
    int parent[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        discovered[i] = FALSE;
        parent[i] = -1;
    }
    discovered[v1] = TRUE;

    while (q->head != NULL) {
        struct AdjList * curr = dequeue(q);
        struct AdjListNode * crawl = curr->head;
        while (crawl != NULL) {
            if (crawl->data == v2) {
                discovered[crawl->data] = TRUE;
                parent[crawl->data] = curr - g->array;
                print_path(parent, v2);
                return TRUE;
            }
            if (!discovered[crawl->data]) {
                enqueue(q, g->array+crawl->data);
                discovered[crawl->data] = TRUE;
                parent[crawl->data] = curr - g->array;
            }
            crawl = crawl->next;
        }
    }
    delete_queue(q);
    return FALSE;
}

/* depth first search */

/*  determine if graph has a cycle

    Assumes graph has a cycle until proven false. First method
    uses DFS to determine if graph is cyclic starting from a 
    given vertex v. Vertex v is initally marked discovered and 
    processed. Each neighbor is processed recursively. If a
    neighbor has been discovered but is still marked processed,
    then there is a back edge and therefore a cycle. The key
    is to unmark a vertex when it has 0 neighbors and return
    up the stack.

    Acyclic graph example

    Start at 0, mark it discovered and processed. Discover and
    process 1, hit NULL, so mark 1 unprocessed. Then discover 
    and process 2, seeing vertex 1 again. Check if vertex 1 
    was marked processed. It was unmarked, so no cycles in
    that branch and unmark 2 as well. 0 gets the signal and
    unmarks itself.
    
         +---+
      +--| 0 |--+
      |  +---+  |
      v         v
    +---+     +---+
    | 1 |<----| 2 |
    +---+     +---+

    Cyclic graph example

    Start at 0, mark it discovered and processed. Discover and
    process 1. Then discover and process 2. Seeing vertex 0 
    again, check if it was marked processed. Vertex 0 is still 
    marked processed. None of 0's neighbors have finished the 
    recursion. Return TRUE up the call stack.

         +---+
      +--| 0 |<-+
      |  +---+  |
      v         |
    +---+     +---+
    | 1 |---->| 2 |
    +---+     +---+

    Running time is Theta(|V| + |E|) for undirected graphs.
    Directed graphs would count each edge twice, |V| + |2E|,
    though that reduces to the same Theta.
*/

int is_cyclic_util(struct Graph * g, int v, int * discovered, int * processed)
{
    struct AdjList * curr = g->array+v;
    struct AdjListNode * crawl = curr->head;
    discovered[v] = TRUE;
    processed[v] = TRUE;
    while (crawl != NULL) {
        if (!discovered[crawl->data]) {
            int finished = is_cyclic_util(g, crawl->data, discovered, processed);
            if (finished) return TRUE;
        } else if (processed[crawl->data] == TRUE) {
            return TRUE;
        }
        crawl = crawl->next;
    }
    processed[v] = FALSE;
    return FALSE;
}

/*  Since the graph may not be connected, need to test every
    vertex. Total running time is therefore Theta(v*(v + e)).
*/

int is_cyclic(struct Graph * g)
{
    int discovered[g->nVertices];
    int processed[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        discovered[i] = 0;
        processed[i] = 0;
    }
    for (int i=0; i<g->nVertices; i++) {
        int finished = is_cyclic_util(g, i, discovered, processed);
        if (finished) return TRUE;
    }
    return FALSE;
}

void topological_sort(struct Graph * g)
{
    ;
}

