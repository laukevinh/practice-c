struct Graph {
    int nVertices;
    int directed;
    int * array;
};

struct Graph * new_graph(int nVertices, int directed);
void add_edge(struct Graph * g, int v1, int v2);
void delete_graph(struct Graph * g);
void print_graph(struct Graph * g);
int connected(struct Graph * g, int v1, int v2);
int shortest_path(struct Graph * g, int v1, int v2);
int is_cyclic(struct Graph * g);
void topological_sort(struct Graph * g, int v);

void test_adjacency_matrix(void);
void test_shortest_path(void);
void test_is_cyclic(void);
void test_topological_sort(void);
