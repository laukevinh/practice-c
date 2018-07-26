#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#define TRUE 1
#define FALSE 0

/*  Adjacency Matrix representation

    +---------------+
    | int nVertices |
    +---------------+      +---+---+---+---+---+
    | pter to array | ---> | 0 | 1 |...|...| n |
    +---------------+      +---+---+---+---+---+

*/

struct Graph * new_graph(int nVertices, int directed)
{
    struct Graph * g = malloc(sizeof(struct Graph));
    g->nVertices = nVertices;
    g->directed = directed;

    int size = nVertices * nVertices;
    g->array = malloc(sizeof(int) * size);

    for (int i=0; i<size; i++)
        g->array[i] = 0;

    return g;
}

/*  add an edge between vertex v1 and vertex v2 */

void add_edge(struct Graph * g, int v1, int v2)
{
    if (v1 > g->nVertices || v2 > g->nVertices) {
        printf("Error Index Out of Bounds\n");
    } else {
        int r = v1;
        int c = v2;
        int pos = c + r * g->nVertices;
        g->array[pos] = 1;
    }
}

/* Utility function to delete graph */

void delete_graph(struct Graph * g)
{
    free(g->array);
    free(g);
}

/* Utility function to print graph */

void print_graph(struct Graph * g)
{
    int pad = 1;
    for (int n=g->nVertices; n>0; n/=10)
        pad++;
    printf("%*s", pad+2, "");
    for (int i=0; i<g->nVertices; i++)
        printf("%d ", i);
    printf("\n");
    for (int i=0; i<g->nVertices; i++) {
        printf("%*d| ", pad, i);
        for (int j=0; j<g->nVertices; j++)
            printf("%d ", g->array[ j+i*g->nVertices ]);
        printf("\n");
    }
}

/*  Breadth first search 

    Use queue to process each vertex. Keep track of
    discovered vertices to avoid revisiting. 
    
    If each vertex is allowed one parent, where parent
    is defined as the vertex that discovers it, then 
    one of the shortest paths between two vertices is 
    the list of parents from vertex 2 to vertex 1. 

    Vertex 1's parent is NULL, so recursively print 
    parents from vertex 2 until NULL. (Used -1 for NULL).
*/

/* prints shortest path using parents */

void print_path(int * parent, int node)
{
    while (parent[node] > 0) {
        printf("%d ", node);
        node = parent[node];
    }
    printf("%d\n", node);
}

int shortest_path(struct Graph * g, int v1, int v2)
{
    int q[g->nVertices];
    int parent[g->nVertices];
    int discovered[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        q[i] = parent[i] = discovered[i] = -1;
    }

    int head = 0;
    int tail = 0;
    q[tail++] = v1;
    discovered[v1] = TRUE;

    while (head < g->nVertices) {
        int curr = q[head++];
        if (curr == v2) {
            print_path(parent, v2);
            return TRUE;
        }
        for (int j=0; j<g->nVertices; j++) {
            int child_ind = curr * g->nVertices + j;
            int child_exists = g->array[child_ind];
            if (child_exists > 0 && discovered[j] < 0) {
                discovered[j] = TRUE;
                q[tail++] = j;
                parent[j] = curr;
            }
        }
    }
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

int is_cyclic_util(struct Graph * g, int v, int * discovered, int * processed, int * parent)
{
    discovered[v] = TRUE;
    processed[v] = FALSE;
    for (int j=0; j<g->nVertices; j++) {
        int child_exists = g->array[v * g->nVertices + j];
        if (child_exists) {
            if (!discovered[j]) {
                parent[j] = v;
                int finished = is_cyclic_util(g, j, discovered, processed, parent);
                if (finished) return TRUE;
            } else if (!processed[j]) {
                if (g->directed) {
                    printf("Cycle at %d, %d\n", v, j);
                    return TRUE;
                } else if (parent[v] != j) {
                    printf("Cycle at %d, %d\n", v, j);
                    return TRUE;
                }
            }
        }
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
    int parent[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        discovered[i] = processed[i] = FALSE;
        parent[i] = -1;
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

int topological_sort_util(struct Graph * g, int v, int * discovered, int * processed, int * order, int * head)
{
    discovered[v] = TRUE;
    processed[v] = FALSE;
    for (int j=0; j<g->nVertices; j++) {
        int child_exists = g->array[ v * g->nVertices + j ];
        if (child_exists) {
            if (!discovered[j]) {
                int finished = topological_sort_util(g, j, discovered, processed, order, head);
                if (finished) return TRUE;
            } else if (!processed[j]) {
                printf("Cycle at %d, %d\n", v, j);
                return TRUE;
            }
        }
    }
    order[*head] = v;
    *head = *head + 1;
    processed[v] = TRUE;
    return FALSE;
}

void topological_sort(struct Graph * g, int v)
{
    int discovered[g->nVertices];
    int processed[g->nVertices];
    int order[g->nVertices];
    for (int i=0; i<g->nVertices; i++) {
        for (int j=0; j<g->nVertices; j++) {
            discovered[j] = processed[j] = FALSE;
            order[j] = FALSE;
        }
        int head = 0;
        int finished = topological_sort_util(g, i, discovered, processed, order, &head);
        if (finished) {
            printf("Not a DAG\n");
        } else {
            while (head > 0) {
                printf("%d ", order[--head]);
            }
            printf("\n");
        }
    }
}

