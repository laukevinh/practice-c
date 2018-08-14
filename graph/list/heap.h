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
void heapify(struct Heap * h); 
/*
void sift_up (struct Heap * h, struct HeapNode n); // needed for insert
struct HeapNode * get_max (struct Heap * h); // returns the max item, without removing it
int get_size(struct Heap * h); // return number of elements stored
int is_empty(struct Heap * h); // returns true if heap contains no elements
struct HeapNode * extract_max(struct Heap * h); // returns the max item, removing it
void sift_down(struct Heap * h); // needed for extract_max
void remove(struct Heap * h, int i); // removes item at index x
void heap_sort(strcut Heap * h); // take an unsorted array and turn it into a sorted array in-place using a max heap
*/
void test_heap(void);
