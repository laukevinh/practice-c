#define HEAP_MIN_CAPACITY 15 
#define HEAP_MIN_HEIGHT 3
#define HEAP_SHRINK_FACTOR 2

struct Heap {
    int count;
    int height;
    int capacity;
    int* data;
};

/* tests */
void test_heap(void);
void test_get_children(void);
void test_max_heapify(void);
void test_pop_max(void);
void test_insert(void);
void test_build_max_heap(void);
