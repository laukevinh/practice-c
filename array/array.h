#define MIN_CAPACITY 16
#define RESIZE_FACTOR 2
#define DOWNSIZE_THRESHOLD 4

/* int array struct */
struct IntArray {
    int len;
    int capacity;
    int* data;
};

/* functions */
struct IntArray* new_array(void);
void delete_array(struct IntArray* intArray);
void resize(struct IntArray* intArray, int new_capacity);
void append(struct IntArray* intArray, int i);
int pop(struct IntArray* intArray);
void insert(struct IntArray* intArray, int i, int pos);
void push(struct IntArray* intArray, int i);
int del(struct IntArray* intArray, int pos);
int pop_front(struct IntArray* intArray);
void update(struct IntArray* intArray, int i, int pos);
int find(struct IntArray* intArray, int x);
int front(struct IntArray* intArray);
int last(struct IntArray* intArray);

/* tests */
void print_array(struct IntArray* intArray);
void test_resize(void);
void test_append(void);
void test_push(void);
void test_pop(void);
void test_pop_front(void);
void test_insert(void);
void test_delete(void);
void test_update(void);
void test_find(void);
void test_front(void);
void test_last(void);
