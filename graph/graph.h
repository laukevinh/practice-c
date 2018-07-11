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
int bfs(struct Graph * g, int start, int dest);
int connected(struct Graph * g, int v1, int v2);

void test_adjacency_list(void);
void test_bfs_1(void);
