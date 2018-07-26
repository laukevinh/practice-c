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

struct Graph * new_graph(int nVertices, int directed)
{
    struct Graph * g = malloc(sizeof(struct Graph));
    g->nVertices = nVertices;
    g->directed = directed;

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

    Vertex 1's parent is NULL, so recursively print 
    parents from vertex 2 until NULL.
*/

/* prints shortest path using parents */

void print_path(struct AdjList ** parent, struct AdjList * node, struct AdjList * root)
{
    int index = (int) (node - root);
    while (parent[index] != NULL) {
        printf("%d ", index); 
        index = (int) (parent[index] - root);
    }
    printf("%d\n", index);
}

int bfs(struct Graph *g, int v1, int v2)
{
    struct Queue * q = new_queue(g->array+v1);

    int discovered[g->nVertices];
    struct AdjList * parent[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        discovered[i] = FALSE;
        parent[i] = NULL;
    }
    discovered[v1] = TRUE;

    while (q->head != NULL) {
        struct AdjList * curr = dequeue(q);
        struct AdjListNode * crawl = curr->head;
        while (crawl != NULL) {
            int i = crawl->data;
            if (i == v2) {
                discovered[i] = TRUE;
                parent[i] = curr;
                print_path(parent, g->array + i, g->array);
                return TRUE;
            }
            if (!discovered[i]) {
                enqueue(q, g->array+i);
                discovered[i] = TRUE;
                parent[i] = curr;
            }
            crawl = crawl->next;
        }
    }
    delete_queue(q);
    return FALSE;
}

/* depth first search */

/*  determine if graph has a cycle

    Use two methods to determine if graph has cycle. First,
    use DFS to determine if graph is cyclic starting from a 
    given vertex v. Vertex v is initally marked discovered and
    unprocessed. Each neighbor is visited recursively. If a
    neighbor has been discovered and marked unprocessed,
    then there is a back edge and therefore a cycle. The key
    is to mark a vertex processed when it has 0 neighbors and 
    return up the stack.

    Acyclic graph example

    Start at 0, mark it discovered and unprocessed. Discover 1,
    mark unprocessed, no neighbors, so mark 1 processed. Then 
    discover 2, mark unprocessed. Vertex 1 is neighbor, already
    discovered. Since it has been processed, no cycles in that
    branch. Vertex 2 has no more neighbors, so mark 2 as
    processed. Vertex 0 gets signal and marks itself processed.
    
         +---+
      +--| 0 |--+
      |  +---+  |
      v         v
    +---+     +---+
    | 1 |<----| 2 |
    +---+     +---+

    Cyclic graph example

    Start at 0, mark it discovered and unprocessed. Discover 1,
    mark unprocessed. Then discover 2, mark unprocessed. 
    Vertex 1 is neighbor, already discovered. Since 1 not yet
    processed, there is a back edge. Return up the call stack.

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

int is_cyclic_util(struct Graph * g, int v, int * discovered, int * processed, struct AdjList ** parent)
{
    struct AdjList * curr = g->array+v;
    struct AdjListNode * crawl = curr->head;
    discovered[v] = TRUE;
    processed[v] = FALSE;
    while (crawl != NULL) {
        if (!discovered[crawl->data]) {
            parent[crawl->data] = curr;
            int finished = is_cyclic_util(g, crawl->data, discovered, processed, parent);
            if (finished) return TRUE;
        } else if (processed[crawl->data] == FALSE) {
            if (g->directed) {
                return TRUE;
            } else if (parent[v] != g->array+crawl->data) {
                return TRUE;
            }
        }
        crawl = crawl->next;
    }
    processed[v] = TRUE;
    return FALSE;
}

/*  Since the graph may not be connected, need to test every
    vertex. Total running time is therefore Theta(v*(v + e)).
*/

int is_cyclic(struct Graph * g)
{
    int discovered[g->nVertices];
    int processed[g->nVertices];
    struct AdjList * parent[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        discovered[i] = FALSE;
        processed[i] = FALSE;
        parent[i] = NULL;
    }
    for (int i=0; i<g->nVertices; i++) {
        int finished = is_cyclic_util(g, i, discovered, processed, parent);
        if (finished) return TRUE;
    }
    return FALSE;
}

/*  topological sort

    Perform DFS starting from vertex v. As each edge is
    processed, push onto a stack. If no back edges, print
    stack LIFO since the deepest item was added to the
    stack first.

    Running time for topological_sort_util is Theta(|V|+|E|)
    then add Theta(|V|) for printing the topological sort.

    Perform topological sort on all nodes means running time
    Theta(v*(v+e)).
*/

int topological_sort_util(struct Graph * g, int v, int * discovered, int * processed, struct Queue * order)
{
    struct AdjList * curr = g->array+v;
    struct AdjListNode * crawl = curr->head;
    discovered[v] = TRUE;
    while (crawl != NULL) {
        if (!discovered[crawl->data]) {
            int finished = topological_sort_util(g, crawl->data, discovered, processed, order);
            if (finished) return TRUE;
        } else if (processed[crawl->data] == FALSE) {
            return TRUE;
        }
        crawl = crawl->next;
    }
    push(order, curr);
    processed[v] = TRUE;
    return FALSE;
}

void topological_sort(struct Graph * g, int v)
{
    int discovered[g->nVertices];
    int processed[g->nVertices];
    struct Queue ord = { NULL, NULL };
    struct Queue * order = &ord;
    for (int i=0; i<g->nVertices; i++) {
        for (int j=0; j<g->nVertices; j++) {
            discovered[j] = FALSE;
            processed[j] = FALSE;
        }
        int finished = topological_sort_util(g, i, discovered, processed, order);
        if (finished) {
            printf("Not a DAG\n");
        } else {
            while (order->head != NULL)
                printf("%d ", (int) (pop(order) - g->array));
            printf("\n");
        }
    }
}

