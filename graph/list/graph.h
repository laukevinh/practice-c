struct AdjListNode {
    int data;
    int weight;
    struct AdjListNode * next;
};

struct AdjList {
    struct AdjListNode * head;
};

struct Graph {
    int nVertices;
    int directed;
    struct AdjList * array;
};

struct Graph * new_graph(int nVertices, int directed);
void add_edge(struct Graph * g, int v1, int v2);
void add_wt_edge(struct Graph * g, int v1, int v2, int wt);
void delete_graph(struct Graph * g);
void print_graph(struct Graph * g);
int connected(struct Graph * g, int v1, int v2);
int shortest_path(struct Graph * g, int start, int dest);
int is_cyclic(struct Graph * g);
void topological_sort(struct Graph * g, int v);
int connected_components(struct Graph * g);
int two_color(struct Graph * g);
void prim_mst(struct Graph * g, int v);

void test_adjacency_list(void);
void test_shortest_path(void);
void test_is_cyclic(void);
void test_topological_sort(void);
void test_connected_components(void);
void test_two_color(void);
void test_weighted_graph(void);
void test_prim_mst(void);
void test_stack(void);

