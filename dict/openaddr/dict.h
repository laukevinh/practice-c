#define MIN_CAPACITY 4
#define RESIZE_FACTOR 2
#define DOWNSIZE_THRESHOLD 0.25
#define UPSIZE_THRESHOLD 0.7

struct Node {
    char *key;
    int val;
};

struct Dict {
    struct Node **head;
    int m;  // capacity
    int n;  // number of elements
};

struct Dict* new_dict(void);
void delete_dict(struct Dict *dict);
struct Node* new_node(char *s, int i);
unsigned long djb2(unsigned char *str);
int pltn(int n);
int hash(unsigned long k, int m, int t);
int resize_tbl(struct Dict * d);
void add(struct Dict *dict, char *key, int value);
int get(struct Dict *dict, char *key);
void del(struct Dict *dict, char *key);

void test_new_dict(void);
void test_get_prime(void);
void test_resize(void);
void test_hash(void);
void test_add(void);
void test_get(void);
void test_del(void);
