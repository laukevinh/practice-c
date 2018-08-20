#define MIN_CAPACITY 16
#define RESIZE_FACTOR 2
#define DOWNSIZE_THRESHOLD 4

struct Edge {
    int v1;
    int v2;
    int wt;
};

struct Heap {
    struct Edge * edges;
    int capacity;
    int size;
};

struct Edge * new_edge(int v1, int v2, int wt);
struct Heap * new_heap(void);
void delete_heap(struct Heap * h);
void insert_heap (struct Heap * h, int v1, int v2, int wt);
struct Edge extract_max (struct Heap * h);
struct Edge get_max(struct Heap * h);
void build_max_heap(struct Heap * h); 
void heap_sort(struct Heap * h);

void insert_min_heap(struct Heap * h, int v1, int v2, int wt);
struct Edge extract_min(struct Heap * h);
struct Edge get_min(struct Heap * h);
void build_min_heap(struct Heap * h);


void test_heap(void);
