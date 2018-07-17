struct AdjListNode {
    int data;
    struct AdjListNode * next;
};

struct AdjList {
    struct AdjListNode * head;
};

struct Graph {
    int nVertices;
    struct AdjList * array;
};

struct Graph * new_graph(int nVertices);
void add_edge(struct Graph * g, int v1, int v2);
void delete_graph(struct Graph * g);
void print_graph(struct Graph * g);
int connected(struct Graph * g, int v1, int v2);
int bfs(struct Graph * g, int start, int dest);
int is_cyclic(struct Graph * g);
void topological_sort(struct Graph * g, int v);

void test_adjacency_list(void);
void test_shortest_path(void);
void test_is_cyclic(void);
void test_topological_sort(void);
void test_stack(void);
