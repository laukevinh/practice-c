
/* int array struct */
struct IntArray {
    int* data;
    int len;
};

/* functions */
struct IntArray* new_array(int len);
void delete_array(struct IntArray* intArray);
void resize(struct IntArray* intArray, int new_len);
void append(struct IntArray* intArray, int i);
void pop(struct IntArray* intArray);
void insert(struct IntArray* intArray, int i, int pos);
void push(struct IntArray* intArray, int i);
void delete(struct IntArray* intArray, int pos);
void pop_front(struct IntArray* intArray);

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
